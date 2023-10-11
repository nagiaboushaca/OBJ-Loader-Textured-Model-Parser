/** @file OBJ.hpp
 *  @brief Class for working with OBJ images
 *  
 *  Class for working with P3 OBJ images specifically.
 *
 *  @author Nagi Aboushaca
 *  @bug No known bugs.
 */
#ifndef OBJ_HPP
#define OBJ_HPP
#include <glm/glm.hpp>
#include <string>

struct Vertex {
    glm::vec3 position;
    glm::vec3 color;
    glm::vec2 texCoord;
    glm::vec3 normal;
};

class OBJ{
public:
    // Constructor loads a filename with the .obj extension
    OBJ(std::string fileName);
    // Destructor clears any memory that has been allocated
    ~OBJ();

    void saveOBJ(std::string fileName);
    
    inline std::vector<float> getVertices() { 
        std::vector<float> output;
        for (int i = 0; i < m_vertices.size(); ++i) {
            output.push_back(m_vertices[i].position.x);
            output.push_back(m_vertices[i].position.y);
            output.push_back(m_vertices[i].position.z);

            output.push_back(m_vertices[i].texCoord.x);
            output.push_back(m_vertices[i].texCoord.y);
        } 
        return output;
    }

    inline std::vector<unsigned int> getIndices() const { return m_indices; }
    inline std::string getPath() const { return m_directory_path; }
    inline std::string getPathToPPM() const { return getPath() + m_ppm_filename; }
private:    
    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;
    std::string m_directory_path;
    std::string m_ppm_filename;
};


#endif
