#include "main.h"
#include <array>
using namespace glm;


//Idee empruntee d'un post sur StackOverflow
//http://stackoverflow.com/questions/9070752/getting-the-bounding-box-of-a-vector-of-points
//L'idee est simple et j'aurais pu la coder avec un paquet de boucle for,
//mais je trouvais l'utilisation de std::minmax_element et des lambdas interessante

//Fonction qui retourne une AABB a partir d'un tableau de vertex
template<std::size_t SIZE>
std::array<vec3, 2> GetAABBBFromVertices(const std::array<VertexPositionNormal, SIZE> &arr_of_vec)
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

//Pour recalculer la AABB a partir dune Bounding Box a laquelle a ete appliquee la matrice de transformation.
std::array<vec3, 2> GetAABBBFromBB(const std::array<vec3, 8> &arr_of_vec);

//Fonction qui retourne les 8 coins d'une Bounding Box selon deux points aux extremites
std::array<vec3, 8> GetBBFromAABB(const std::array<vec3, 2> &arr_of_vec);

std::array<vec3, 3> GetNormalsFromBB(const std::array<vec3, 8>& bounding_box);
	
vec3 GetCenterFromBB(const std::array<vec3, 8>& bounding_box);

std::array<vec3, 3> GetExtentsFromBB(const std::array<vec3, 8>& bounding_box);

class BoundingBox{
public:
	BoundingBox(const std::array<vec3,2>& arr);
};
	