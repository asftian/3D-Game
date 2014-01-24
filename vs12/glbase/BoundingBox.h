using glm::vec3;

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
std::array<vec3, 2> GetAABBBFromBB(const std::array<vec3, 8> &arr_of_vec)
{
	auto resultX = std::minmax_element(arr_of_vec.begin(), arr_of_vec.end(), [](const vec3& lhs, const vec3& rhs) {
		return lhs.x < rhs.x;
	});
	auto resultY = std::minmax_element(arr_of_vec.begin(), arr_of_vec.end(), [](const vec3& lhs, const vec3& rhs) {
		return lhs.y < rhs.y;
	});
	auto resultZ = std::minmax_element(arr_of_vec.begin(), arr_of_vec.end(), [](const vec3& lhs, const vec3& rhs) {
		return lhs.z < rhs.z;
	});

	vec3 corner_max{ resultX.second->x, resultY.second->y, resultZ.second->z };
	vec3 corner_min{ resultX.first->x, resultY.first->y, resultZ.first->z };
	std::array<vec3, 2> results = { corner_max, corner_min };
	return results;
}

//Fonction qui retourne les 8 coins d'une Bounding Box selon deux points aux extremites
std::array<vec3, 8> GetBBFromAABB(const std::array<vec3, 2> &arr_of_vec)
{
	
	
	vec3 corner_fur{ arr_of_vec[0].x, arr_of_vec[0].y, arr_of_vec[0].z };
	vec3 corner_rbl{ arr_of_vec[1].x, arr_of_vec[1].y, arr_of_vec[1].z };
	vec3 corner_fbr{ corner_fur.x, corner_rbl.y, corner_fur.z };
	vec3 corner_ful{ corner_fur.x, corner_fur.y, corner_rbl.z };
	vec3 corner_fbl{ corner_fur.x, corner_rbl.y, corner_rbl.z };
	vec3 corner_rur{ corner_rbl.x, corner_fur.y, corner_fur.z };
	vec3 corner_rul{ corner_rbl.x, corner_fur.y, corner_rbl.z };
	vec3 corner_rbr{ corner_rbl.x, corner_rbl.y, corner_fur.z };

	std::array<vec3, 8> results = {  corner_fur, corner_rbl, corner_fbr, corner_ful, corner_fbl, corner_rur, corner_rul, corner_rbr  };

	return results;
}

std::array<vec3, 6> GetNormalsFromBB(const std::array<vec3, 8>& bounding_box){
	std::array<vec3, 6> normals;
	return normals;
}