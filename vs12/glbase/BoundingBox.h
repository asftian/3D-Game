#include <main.h>
#include <array>
#include <iomanip>
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
	std::array<float, 3> GetExtents() const;
	std::array<vec3, 3> GetNormals() const;
	void SetTransform(mat4& mat);
	int set = 0;
	virtual ~BoundingBox();
	void print(std::string name){
		std::cout << name << std::endl;
		std::cout << "center is " << center.x << "," << center.y << "," << center.z << "\n";
		std::cout << "normals are \n" << normals[0].x << "," << normals[0].y << "," << normals[0].z << "\n" << normals[1].x << "," << normals[1].y << "," << normals[1].z << "\n" << normals[2].x << "," << normals[2].y << "," << normals[2].z << "\n";
		bool test = false;
		float scal = dot(normals[0], normals[1]);
		std::cout << "first dot product " << scal << "\n";

		scal = dot(normals[0], normals[2]);
		std::cout << "second dot product " << scal << "\n";

		scal = dot(normals[1], normals[2]);
		std::cout << "third dot product " << scal << "\n";


		
		std::cout << "extents are " << extents[0] << ","<< extents[1] << ","<< extents[2] << "\n";
		for (int i = 0; i < 8; i++){
			
			printf ("%1.2f , %1.2f, %1.2f\n", points[i].x, points[i].y, points[i].z);
		}
		printf("\n");
		
	}
protected:
	std::array<vec3, 2> aabb;
	std::array<vec3, 8> points;
	std::array<vec3, 8> init_points;
	std::array<vec3, 3> normals;
	std::array<vec3, 3> init_normals;
	std::array<float, 3> extents;
	std::array<float, 3> init_extents;
	vec3 center;
	
	void SetCenter();
	void SetNormals();
	void SetExtents();
	void SetAABB();
};
