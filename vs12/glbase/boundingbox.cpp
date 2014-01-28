#include "boundingbox.h"
BoundingBox::BoundingBox(){
	set = 0;
}
BoundingBox::BoundingBox(const std::array<vec3, 2>& arr){
	set = 1;
	vec3 corner_fur{ arr[0].x, arr[0].y, arr[0].z };
	vec3 corner_rbl{ arr[1].x, arr[1].y, arr[1].z };
	vec3 corner_fbr{ corner_fur.x, corner_rbl.y, corner_fur.z };
	vec3 corner_ful{ corner_fur.x, corner_fur.y, corner_rbl.z };
	vec3 corner_fbl{ corner_fur.x, corner_rbl.y, corner_rbl.z };
	vec3 corner_rur{ corner_rbl.x, corner_fur.y, corner_fur.z };
	vec3 corner_rul{ corner_rbl.x, corner_fur.y, corner_rbl.z };
	vec3 corner_rbr{ corner_rbl.x, corner_rbl.y, corner_fur.z };

	init_points = { { corner_fur, corner_rbl, corner_fbr, corner_ful, corner_fbl, corner_rur, corner_rul, corner_rbr } };
	points = init_points;
	SetCenter();
	SetNormals();
	SetExtents();
	SetAABB();
}


void BoundingBox::SetAABB(){
	auto resultX = std::minmax_element(points.begin(), points.end(), [](const vec3& lhs, const vec3& rhs) {
		return lhs.x < rhs.x;
	});
	auto resultY = std::minmax_element(points.begin(), points.end(), [](const vec3& lhs, const vec3& rhs) {
		return lhs.y < rhs.y;
	});
	auto resultZ = std::minmax_element(points.begin(), points.end(), [](const vec3& lhs, const vec3& rhs) {
		return lhs.z < rhs.z;
	});

	vec3 corner_max{ resultX.second->x, resultY.second->y, resultZ.second->z };
	vec3 corner_min{ resultX.first->x, resultY.first->y, resultZ.first->z };

	
	aabb[0] = corner_max;
	aabb[1] = corner_min;
}

std::array<vec3, 2> BoundingBox::GetAABB() const{
	return aabb;
}

vec3 BoundingBox::GetCenter() const{
	return center;
}

std::array<vec3, 3> BoundingBox::GetExtents() const{
	return extents;
}
std::array<vec3, 3> BoundingBox::GetNormals() const{
	return normals;
}
void BoundingBox::SetTransform(mat4& mat){

	for (int i = 0; i < 8; i++){
		vec4 v4(init_points[i], 1);
		v4 = (mat*v4);
		vec3 v3(v4);
		points[i] = v3;
	}
	SetCenter();
	SetNormals();
	SetExtents();
	SetAABB();
}

void BoundingBox::SetNormals(){
	normals.at(0) = normalize(points.at(4) - points.at(1));
	normals.at(1) = normalize(points.at(6) - points.at(1));
	normals.at(2) = normalize(points.at(7) - points.at(1));
}
void BoundingBox::SetCenter(){
	center.x = points.at(5).x + (points.at(0).x - points.at(5).x) / 2;
	center.y = points.at(2).y + (points.at(0).y - points.at(2).y) / 2;
	center.z = points.at(3).z + (points.at(0).z - points.at(3).z) / 2;
}
void BoundingBox::SetExtents(){
	extents.at(0) = vec3(points.at(3).x - center.x, 0, 0);
	extents.at(1) = vec3(0, points.at(0).y - center.y, 0);
	extents.at(2) = vec3(0, 0, points.at(0).z - center.z);
}

BoundingBox::~BoundingBox(){

}