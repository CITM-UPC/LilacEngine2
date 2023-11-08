#pragma once

#include <vector>
#include <memory>
#include <string>

#include "types.h"
#include "Graphic.h"
#include "Texture2D.h"

class Mesh :
	public Graphic
{
public:
	enum Formats { F_V3, F_V3C4, F_V3T2 };
	struct V3 { vec3f v; }; //Vector 3 points
	struct V3C4 { vec3f v; vec4f c; }; //Vector 3 points, color
	struct V3T2 { vec3f v; vec2f t; }; //Vector 3 points, texture 2D

private:
	const enum Formats _format;

	unsigned int _vertex_buffer_id = 0;
	const unsigned int _numVerts;

	unsigned int _indexs_buffer_id = 0;
	const unsigned int _numIndexs;

	const unsigned int _numFaces;

public:
	using Ptr = std::shared_ptr<Mesh>;

	static std::vector<Ptr> loadFromFile(const std::string& path);
	static std::vector<Ptr> loadFromFile(const std::string& path, const std::string& stringPath);

	std::string path;

	void loadTextureToMesh(const std::string& path);
	Texture2D::Ptr texture;

	Texture2D::Ptr checkboard = std::shared_ptr<Texture2D>(new Texture2D);
	bool drawChecker = false;

	std::vector<vec3f> meshVerts;
	std::vector<vec3f> meshNorms;
	std::vector<vec3f> meshFaceCenters;
	std::vector<vec3f> meshFaceNorms;

	bool drawNormalsVerts = false;
	bool drawNormalsFaces = false;

	Mesh(Formats format, const void* vertex_data, unsigned int numVerts, unsigned int numFaces, const unsigned int* index_data = nullptr, unsigned int numIndexs = 0);
	Mesh(Mesh&& b) noexcept;
	void draw();
	~Mesh();


	const unsigned int getFacesNum();
	const unsigned int getVertsNum();
	//const unsigned int getNormNum();

	int normalLineWidth = 1;
	float normalLineLength = 0.1f;

private:
	Mesh(const Mesh& cpy);
	Mesh& operator=(const Mesh&);

};