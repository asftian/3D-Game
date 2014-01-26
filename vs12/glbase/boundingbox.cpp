#include "boundingbox.h"

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

	std::array<vec3, 8> results = { corner_fur, corner_rbl, corner_fbr, corner_ful, corner_fbl, corner_rur, corner_rul, corner_rbr };

	return results;
}

std::array<vec3, 3> GetNormalsFromBB(const std::array<vec3, 8>& bounding_box){
	std::array<vec3, 3> normals;
	normals[0] = normalize(bounding_box.at(4) - bounding_box.at(1));
	normals[1] = normalize(bounding_box.at(6) - bounding_box.at(1));
	normals[2] = normalize(bounding_box.at(7) - bounding_box.at(1));
	return normals;
}

vec3 GetCenterFromBB(const std::array<vec3, 8>& bounding_box){
	float x = bounding_box.at(5).x + (bounding_box.at(0).x - bounding_box.at(5).x) / 2;
	float y = bounding_box.at(2).y + (bounding_box.at(0).y - bounding_box.at(2).y) / 2;
	float z = bounding_box.at(3).z + (bounding_box.at(0).z - bounding_box.at(3).z) / 2;
	return vec3(x, y, z);
}
std::array<vec3, 3> GetExtentsFromBB(const std::array<vec3, 8>& bounding_box){
	std::array<vec3, 3> extents;
	vec3 center = GetCenterFromBB(bounding_box);
	extents.at(0) = vec3(bounding_box.at(3).x - center.x, 0, 0);
	extents.at(1) = vec3(0, bounding_box.at(0).y - center.y, 0);
	extents.at(2) = vec3(0, 0, bounding_box.at(0).z - center.z);
	return extents;
}
