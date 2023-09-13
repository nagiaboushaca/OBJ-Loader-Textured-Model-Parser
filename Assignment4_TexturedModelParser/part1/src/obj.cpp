#include "OBJ.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <glad/glad.h>
#include <glm/glm.hpp>


// Constructor loads a filename with the .obj extension
OBJ::OBJ(std::string fileName){
    
    
    std::ifstream input;

    input.open(fileName);

    std::string path = fileName.substr(0, fileName.find_last_of('/') + 1);
    m_directory_path = path;

    if(!input.is_open()) {
        std::cout << "Filepath does not exist" << fileName << std::endl;
        std::cout << "Make sure your path is correct relative to where you execute the program" << std::endl;
    } 

    std::string line;

    std::vector<glm::vec3> vertex_positions;
    std::vector<glm::vec2> vertex_textures;
    std::vector<glm::vec3> vertex_normals;

    std::vector<unsigned int> vertex_position_indicies;
    std::vector<unsigned int> vertex_texture_indicies;
    std::vector<unsigned int> vertex_normal_indicies;

    while(getline(input, line)) { 
        std::stringstream stream(line);
        std::string token;
        while(stream >> token) {
            if(token.front() == 'v' && token.size() == 1) {
                glm::vec3 position;
                stream >> position.x >> position.y >> position.z;
                vertex_positions.push_back(position);
            } else if(token == "vn") {
                glm::vec3 normal;
                stream >> normal.x >> normal.y >> normal.z;
                vertex_normals.push_back(normal);
            } else if(token == "vt") {
                glm::vec2 texCoord;
                stream >> texCoord.x >> texCoord.y;
                vertex_textures.push_back(texCoord);
            } else if(token.front() == 'f') {
                std::string vertexData;
                for (unsigned int i = 0; i < 3; ++i) {
                 stream >> vertexData;
                    std::istringstream viss(vertexData);
                    std::string indexStr;
                    std::getline(viss, indexStr, '/');
                    unsigned int positionIndex = std::stoi(indexStr) - 1;
                    vertex_position_indicies.push_back(positionIndex);

                    std::getline(viss, indexStr, '/');
                    unsigned int texCoordIndex = std::stoi(indexStr) - 1;
                    vertex_texture_indicies.push_back(texCoordIndex);
                    

                    std::getline(viss, indexStr, '/');
                    unsigned int normalIndex = std::stoi(indexStr) - 1;
                    vertex_normal_indicies.push_back(normalIndex);
                }
            } else if (token == "mtllib") {
                std::string mtlFilename;
                stream >> mtlFilename;
                std::string mtlFilepath = m_directory_path + mtlFilename;
                std::ifstream mtl;
                mtl.open(mtlFilepath);

                if(!mtl.is_open()) {
                    std::cout << "Mtl filepath does not exist: " << mtlFilepath << std::endl;
                } 

                std::string mtlLine;
                while(getline(mtl, mtlLine)) {
                    std::stringstream mtlStream(mtlLine);
                    std::string mtlToken;
                    while(mtlStream >> mtlToken) {
                        if (mtlToken == "map_Kd") {
                            mtlStream >> m_ppm_filename;
                        }
                    }
                }
                mtl.close();
            }
        }
        // std::cout << m_ppmFilename << std::endl;  
        // std::cout << i << std::endl;  
    }

    m_vertices.resize(vertex_position_indicies.size());

    for (int i = 0; i < m_vertices.size(); ++i) {
        
        m_vertices[i].position = vertex_positions[vertex_position_indicies[i]];
        m_vertices[i].color = glm::vec3(0.f, 0.f, 0.f);
        m_vertices[i].texCoord = vertex_textures[vertex_texture_indicies[i]];
        m_vertices[i].normal = vertex_normals[vertex_normal_indicies[i]];
        m_indices.push_back(i);
    }

    for (int i = 0; i < getIndices().size(); ++i) {
        std::cout << getIndices()[i] << std::endl;
    }
    
    
    

  input.close();
}

// Destructor deletes(delete or delete[]) any memory that has been allocated
// or otherwise calls any 'shutdown' or 'destroy' routines for this deletion
// to occur. This class does not have any dynamically allocated memory using
// "new", so the destructor is empty
OBJ::~OBJ(){}

void OBJ::saveOBJ(std::string fileName) {
    std::ofstream outFile;
    outFile.open(fileName);

    for (int i = 0; i < getVertices().size(); ++i) {
        outFile << getVertices()[i] << std::endl;
    }

    outFile.close();
}



