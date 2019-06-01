#ifndef MODEL_HPP
#define MODEL_HPP
#define STB_IMAGE_IMPLEMENTATION

#include <mesh.hpp>
#include <shader.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>

using namespace std;

// load and generate textures from the object file
unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false);

struct Dimension
{
    float min;
    float max;
    float center;
    float size;
};

struct BoundingBox
{
    Dimension x;
    Dimension y;
    Dimension z;
};

class Model 
{
public:
    /*  Model Data */
    vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    vector<Mesh> meshes;
    string directory;
    bool gammaCorrection;
    BoundingBox boundingBox;

    /*  Functions   */
    // constructor, expects a filepath to a 3D model.
    Model(string const &path, bool gamma = false);

    // draws the model, and thus all its meshes
    void Draw(Shader shader);

    // calculate the bounding box of the model
    void calcBoundingBox();

    // find the size of the biggest dimension of the bounding box
    float biggestDimensionSize();

private:
    /*  Functions   */
    // loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
    void loadModel(string const &path);

    // processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
    void processNode(aiNode *node, const aiScene *scene);

    Mesh processMesh(aiMesh *mesh, const aiScene *scene);

    // checks all material textures of a given type and loads the textures if they're not loaded yet.
    // the required info is returned as a Texture struct.
    vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);

    // finds the lowest and highest vertices of the model on the X axis
    Dimension xLimits();
    
    // finds the lowest and highest vertices of the model on the Y axis
    Dimension yLimits();

    // finds the lowest and highest vertices of the model on the Z axis
    Dimension zLimits();
};

#endif
