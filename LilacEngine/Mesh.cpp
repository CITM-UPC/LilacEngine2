#include "Mesh.h"
#include <GL/glew.h>

#include <assimp/postprocess.h>
#include <assimp/cimport.h>
#include <assimp/scene.h>

#include <span>

#include <vector>
#include <array>

#include <filesystem>
namespace fs = std::filesystem;

using namespace std;

struct aiMeshExt : aiMesh {
    auto verts() const { return span((vec3f*)mVertices, mNumVertices); }
    auto texCoords() const { return span((vec3f*)mTextureCoords[0], mNumVertices); }
    auto faces() const { return span(mFaces, mNumFaces); }
};

struct aiSceneExt : aiScene {
    auto materials() const { return span(mMaterials, mNumMaterials); }
    auto meshes() const { return span((aiMeshExt**)mMeshes, mNumMeshes); }
};


std::vector<Mesh::Ptr> Mesh::loadFromFile(const std::string& path) {
    const auto scene_ptr = aiImportFile(path.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_ForceGenNormals);
    const aiSceneExt& scene = *(aiSceneExt*)scene_ptr;

    //load textures
    vector<Texture2D::Ptr> texture_ptrs;
    for (const auto& material : scene.materials()) {
        aiString aiPath;
        material->GetTexture(aiTextureType_DIFFUSE, 0, &aiPath);
        fs::path texPath = fs::path(path).parent_path() / fs::path(aiPath.C_Str()).filename();
        auto texture_ptr = make_shared<Texture2D>(texPath.string());
        texture_ptrs.push_back(texture_ptr);
    }

    //load meshes
    vector<Mesh::Ptr> mesh_ptrs;
    for (const auto& mesh_ptr : scene.meshes()) {

        const auto& mesh = *mesh_ptr;

        vector<V3T2> vertex_data;
        for (size_t i = 0; i < mesh.verts().size(); ++i) {
            V3T2 v = { mesh.verts()[i], vec2f(mesh.texCoords()[i].x, mesh.texCoords()[i].y) };
            vertex_data.push_back(v);
        }

        vector<unsigned int> index_data;
        for (const auto& face : mesh.faces()) {
            index_data.push_back(face.mIndices[0]);
            index_data.push_back(face.mIndices[1]);
            index_data.push_back(face.mIndices[2]);

        }

        auto mesh_sptr = make_shared<Mesh>(Formats::F_V3T2, vertex_data.data(), vertex_data.size(), mesh.mNumFaces, index_data.data(), index_data.size());
        mesh_sptr->texture = texture_ptrs[mesh.mMaterialIndex];
        mesh_sptr->path = path;

        for (size_t i = 0; i < mesh.mNumVertices; i++) {
            aiVector3D normal = mesh.mNormals[i];
            vec3f glmNormal(normal.x, normal.y, normal.z);
            mesh_sptr->meshNorms.push_back(glmNormal);
        }

        for (size_t i = 0; i < mesh.mNumVertices; i++) {
            aiVector3D vert = mesh.mVertices[i];
            vec3f glmNormal(vert.x, vert.y, vert.z);
            mesh_sptr->meshVerts.push_back(glmNormal);
        }

        for (size_t i = 0; i < mesh.mNumFaces; i++) {
            aiFace face = mesh.mFaces[i];

            vec3f v0(mesh.mVertices[face.mIndices[0]].x, mesh.mVertices[face.mIndices[0]].y, mesh.mVertices[face.mIndices[0]].z);
            vec3f v1(mesh.mVertices[face.mIndices[1]].x, mesh.mVertices[face.mIndices[1]].y, mesh.mVertices[face.mIndices[1]].z);
            vec3f v2(mesh.mVertices[face.mIndices[2]].x, mesh.mVertices[face.mIndices[2]].y, mesh.mVertices[face.mIndices[2]].z);

            vec3f faceNormal = glm::cross(v1 - v0, v2 - v0);
            faceNormal = glm::normalize(faceNormal);
            mesh_sptr->meshFaceNorms.push_back(faceNormal);

            vec3f faceCenter = (v0 + v1 + v2) / 3.0f;
            mesh_sptr->meshFaceCenters.push_back(faceCenter);
        }


        mesh_ptrs.push_back(mesh_sptr);
    }

    aiReleaseImport(scene_ptr);

    return mesh_ptrs;
}

std::vector<Mesh::Ptr> Mesh::loadFromFile(const std::string& path, const std::string& stringPath) {


    const auto scene_ptr = aiImportFile(path.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_ForceGenNormals);
    const aiSceneExt& scene = *(aiSceneExt*)scene_ptr;

    //load textures
    vector<Texture2D::Ptr> texture_ptrs;
    for (const auto& material : scene.materials()) {
        aiString aiPath(stringPath);
        fs::path texPath = fs::path(stringPath).parent_path() / fs::path(aiPath.C_Str()).filename();
        auto texture_ptr = make_shared<Texture2D>(texPath.string());
        texture_ptrs.push_back(texture_ptr);
    }

    //load meshes
    vector<Mesh::Ptr> mesh_ptrs;
    for (const auto& mesh_ptr : scene.meshes()) {

        const auto& mesh = *mesh_ptr;

        vector<V3T2> vertex_data;
        for (size_t i = 0; i < mesh.verts().size(); ++i) {
            V3T2 v = { mesh.verts()[i], vec2f(mesh.texCoords()[i].x, mesh.texCoords()[i].y) };
            vertex_data.push_back(v);
        }

        vector<unsigned int> index_data;
        for (const auto& face : mesh.faces()) {
            // push back each vertex from the triangles
            index_data.push_back(face.mIndices[0]);
            index_data.push_back(face.mIndices[1]);
            index_data.push_back(face.mIndices[2]);
        }

        auto mesh_sptr = make_shared<Mesh>(Formats::F_V3T2, vertex_data.data(), vertex_data.size(), mesh.mNumFaces, index_data.data(), index_data.size());
        mesh_sptr->texture = texture_ptrs[mesh.mMaterialIndex];
        mesh_sptr->path = path;

        for (size_t i = 0; i < mesh.mNumVertices; i++) {
            aiVector3D normal = mesh.mNormals[i];
            vec3f glmNormal(normal.x, normal.y, normal.z);
            mesh_sptr->meshNorms.push_back(glmNormal);
        }

        for (size_t i = 0; i < mesh.mNumVertices; i++) {
            aiVector3D vert = mesh.mVertices[i];
            vec3f glmNormal(vert.x, vert.y, vert.z);
            mesh_sptr->meshVerts.push_back(glmNormal);
        }

        for (size_t i = 0; i < mesh.mNumFaces; i++) {
            aiFace face = mesh.mFaces[i];

            vec3f v0(mesh.mVertices[face.mIndices[0]].x, mesh.mVertices[face.mIndices[0]].y, mesh.mVertices[face.mIndices[0]].z);
            vec3f v1(mesh.mVertices[face.mIndices[1]].x, mesh.mVertices[face.mIndices[1]].y, mesh.mVertices[face.mIndices[1]].z);
            vec3f v2(mesh.mVertices[face.mIndices[2]].x, mesh.mVertices[face.mIndices[2]].y, mesh.mVertices[face.mIndices[2]].z);

            vec3f faceNormal = glm::cross(v1 - v0, v2 - v0);
            faceNormal = glm::normalize(faceNormal);
            mesh_sptr->meshFaceNorms.push_back(faceNormal);

            vec3f faceCenter = (v0 + v1 + v2) / 3.0f;
            mesh_sptr->meshFaceCenters.push_back(faceCenter);
        }


        mesh_ptrs.push_back(mesh_sptr);
    }

    aiReleaseImport(scene_ptr);

    return mesh_ptrs;
}

void Mesh::loadTextureToMesh(const std::string& path)
{
    aiString aiPath(path);
    fs::path texPath = fs::path(path).parent_path() / fs::path(aiPath.C_Str()).filename();
    auto texture_ptr = make_shared<Texture2D>(texPath.string());
    texture = texture_ptr;

}

Mesh::Mesh(Formats format, const void* vertex_data, unsigned int numVerts, unsigned int numFaces, const unsigned int* index_data, unsigned int numIndexs) :
    _format(format),
    _numVerts(numVerts),
    _numIndexs(numIndexs),
    _numFaces(numFaces)
{

    glGenBuffers(1, &_vertex_buffer_id);
    glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer_id);

    switch (_format) {
    case Formats::F_V3:
        glBufferData(GL_ARRAY_BUFFER, sizeof(V3) * numVerts, vertex_data, GL_STATIC_DRAW);
        break;
    case Formats::F_V3C4:
        glBufferData(GL_ARRAY_BUFFER, sizeof(V3C4) * numVerts, vertex_data, GL_STATIC_DRAW);
        break;
    case Formats::F_V3T2:
        glBufferData(GL_ARRAY_BUFFER, sizeof(V3T2) * numVerts, vertex_data, GL_STATIC_DRAW);
        break;
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    if (index_data) {
        glGenBuffers(1, &_indexs_buffer_id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexs_buffer_id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * numIndexs, index_data, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    else {
        _indexs_buffer_id = 0;
    }
}


Mesh::Mesh(Mesh&& b) noexcept :
    _format(b._format),
    _vertex_buffer_id(b._vertex_buffer_id),
    _numVerts(b._numVerts),
    _indexs_buffer_id(b._indexs_buffer_id),
    _numIndexs(b._numIndexs),
    _numFaces(b._numFaces),
    texture(b.texture)
{
    meshVerts = b.meshVerts;
    meshNorms = b.meshNorms;
    meshFaceCenters = b.meshFaceCenters;
    meshFaceNorms = b.meshFaceNorms;


    b._vertex_buffer_id = 0;
    b._indexs_buffer_id = 0;

}

void Mesh::draw() {

    glColor4ub(255, 255, 255, 255);

    glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer_id);
    glEnableClientState(GL_VERTEX_ARRAY);

    switch (_format) {
    case Formats::F_V3:
        glVertexPointer(3, GL_FLOAT, 0, nullptr);
        break;
    case Formats::F_V3C4:
        glEnableClientState(GL_COLOR_ARRAY);
        glVertexPointer(3, GL_FLOAT, sizeof(V3C4), nullptr);
        glColorPointer(4, GL_FLOAT, sizeof(V3C4), (void*)sizeof(V3));
        break;
    case Formats::F_V3T2:
        glEnable(GL_TEXTURE_2D);
        if (texture.get() && drawChecker == false)
        {
            texture->bind();
        }
        else {
            checkboard.get()->bind();
        }
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glVertexPointer(3, GL_FLOAT, sizeof(V3T2), nullptr);
        glTexCoordPointer(2, GL_FLOAT, sizeof(V3T2), (void*)sizeof(V3));
        break;
    }

    if (_indexs_buffer_id) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexs_buffer_id);
        glDrawElements(GL_TRIANGLES, _numIndexs, GL_UNSIGNED_INT, nullptr);
    }
    else {
        glDrawArrays(GL_TRIANGLES, 0, _numVerts);
    }

    if (drawNormalsVerts && !meshVerts.empty() && !meshNorms.empty()) {
        glLineWidth(normalLineWidth);
        glBegin(GL_LINES);
        glColor3f(1.0f, 1.0f, 0.0f);

        for (int i = 0; i < _numVerts; i++) {
            glVertex3f(meshVerts[i].x, meshVerts[i].y, meshVerts[i].z);
            glVertex3f(meshVerts[i].x + meshNorms[i].x * normalLineLength,
                meshVerts[i].y + meshNorms[i].y * normalLineLength,
                meshVerts[i].z + meshNorms[i].z * normalLineLength);
        }

        glColor3f(1.0f, 1.0f, 0.0f);
        glEnd();
    }

    if (drawNormalsFaces && !meshFaceCenters.empty() && !meshFaceNorms.empty()) {
        glLineWidth(normalLineWidth);
        glBegin(GL_LINES);
        glColor3f(1.0f, 0.0f, 1.0f);

        for (int i = 0; i < _numFaces; i++) {
            glm::vec3 endPoint = meshFaceCenters[i] + normalLineLength * meshFaceNorms[i];
            glVertex3f(meshFaceCenters[i].x, meshFaceCenters[i].y, meshFaceCenters[i].z);
            glVertex3f(endPoint.x, endPoint.y, endPoint.z);
        }

        glColor3f(0.0f, 1.0f, 1.0f);
        glEnd();
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisable(GL_TEXTURE_2D);
}


Mesh::~Mesh() {
    if (_vertex_buffer_id) glDeleteBuffers(1, &_vertex_buffer_id);
    if (_indexs_buffer_id) glDeleteBuffers(1, &_indexs_buffer_id);
}

const unsigned int Mesh::getFacesNum()
{
    return _numFaces;
}

const unsigned int Mesh::getVertsNum()
{
    return _numVerts;
}