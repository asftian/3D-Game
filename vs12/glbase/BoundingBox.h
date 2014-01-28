#include <main.h>
#include <array>
using namespace glm;
struct VertexPositionNormal
{
	vec3 position;
	vec3 normal;
};

//Idee empruntee d'un post sur StackOverflow
//http://stackoverflow.com/questions/9070752/getting-the-bounding-box-of-a-vector-of-points
//L'idee est simple et j'aurais pu la coder avec un paquet de boucle for,
//mais je trouvais l'utilisation de std::minmax_element et des lambdas interessante

//Fonction qui retourne une AABB a partir d'un tableau de vertex
template<std::size_t SIZE>
std::array<vec3, 2> GetAABBFromVertices(const std::array<VertexPositionNormal, SIZE> &arr_of_vec)
{
	auto resultX = std::minmax_element(arr_of_vec.begin(), arr_of_vec.end(), [](const VertexPositionNormal& lhs, const VertexPositionNormal& rhs) {
		return lhs.position.x < rhs.position.x;
	});
	auto resultY = std::minmax_element(arr_of_vec.begin(), arr_of_vec.end(), [](const VertexPositionNormal& lhs, const VertexPositionNormal& rhs) {
		return lhs.position.y < rhs.position.y;
	});
	auto resultZ = std::minmax_element(arr_of_vec.begin(), arr_of_vec.end(), [](const VertexPositionNormal& lhs, const VertexPositionNormal& rhs) {
		return lhs.position.z < rhs.position.z;
	});

	vec3 corner_max{ resultX.second->position.x, resultY.second->position.y, resultZ.second->position.z };
	vec3 corner_min{ resultX.first->position.x, resultY.first->position.y, resultZ.first->position.z };
	std::array<vec3, 2> results = { corner_max, corner_min };
	return results;
}


class BoundingBox{
public:
	BoundingBox();
	//Prend en entree une axis oriented bounding box de 2 points
	BoundingBox(const std::array<vec3,2>& arr);

	//AABB business

	void setAABB();
	std::array<vec3, 2> GetAABB() const;
	//OBB business
	vec3 GetCenter() const;
	std::array<vec3, 3> GetExtents() const;
	std::array<vec3, 3> GetNormals() const;
	void SetTransform(mat4& mat);
	int set = 0;
	virtual ~BoundingBox();
protected:
	std::array<vec3, 2> aabb;
	std::array<vec3, 8> points;
	std::array<vec3, 8> init_points;
	std::array<vec3, 3> normals;
	std::array<vec3, 3> extents;
	vec3 center;
	
	void SetCenter();
	void SetNormals();
	void SetExtents();
	void SetAABB();
};
