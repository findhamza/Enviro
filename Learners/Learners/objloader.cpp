#include "objloader.h"

objloader::objloader(std::string path) {

	src = path;

	if (verifyFile()) {
		setParam();
		processParam();
	}
}

void objloader::draw() {


	/*glColor3f(1.0f, 0.5f, 0.0f); //white color
	glBegin(GL_TRIANGLES);
	for (auto value : out_vertices)
		glVertex3f(value.x, value.y, value.z);
	glEnd();*/
	GLfloat lightpos[] = { 10, 10, 10, 1 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
	GLfloat red[] = { 1.f, 0.f, 0.f, 1.f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, red);
	glColor3f(1.0f, 0.0f, 0.0f); //black color
	glBegin(GL_TRIANGLES);
	for (auto value : out_vertices)
		glVertex3f(value.x, value.y, value.z);
	glEnd();
	glRotatef(1.0, 0.0, 1.0, 0.0);
	glScalef(0.99, 0.99, 0.99);
}

std::vector<glm::vec3> objloader::getVertices() {
	return out_vertices;
}

std::vector<glm::vec2> objloader::getUvs() {
	return out_uvs;
}

std::vector<glm::vec3> objloader::getNormals() {
	return out_normals;
}

bool objloader::verifyFile() {

	const char* charSrc = src.c_str();
	errno_t errFile = fopen_s(&file, charSrc, "r");

	return !errFile;
}

void objloader::setParam() {

	while (true) {
		char lineHeader[128];

		int res = fscanf_s(file, "%s", lineHeader, _countof(lineHeader));
		if (res == EOF)
			break;
		else {
			if (strcmp(lineHeader, "v") == 0) {
				glm::vec3 vertex;
				fscanf_s(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
				temp_vertices.push_back(vertex);
			}
			else if (strcmp(lineHeader, "vt") == 0) {
				glm::vec2 uv;
				fscanf_s(file, "%f %f\n", &uv.x, &uv.y);
				temp_uvs.push_back(uv);
			}
			else if (strcmp(lineHeader, "vn") == 0) {
				glm::vec3 normal;
				fscanf_s(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
				temp_normals.push_back(normal);
			}
			else if (strcmp(lineHeader, "f") == 0) {
				std::string vertex1, vertex2, vertex3;
				unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
				int matches = fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
				if (matches != 9) {
					printf("File can't be read by our simple parser : ( Try exporting with other options\n");
					break;
				}
				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);
				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[1]);
				uvIndices.push_back(uvIndex[2]);
				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);
			}
		}
	}
}

void objloader::processParam()
{
	for (unsigned int i = 0; i < vertexIndices.size(); i++) {
		unsigned int vertexIndex = vertexIndices[i];
		glm::vec3 vertex = temp_vertices[vertexIndex - 1];
		out_vertices.push_back(vertex);
	}
}
