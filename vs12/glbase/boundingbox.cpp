#include "boundingbox.h"
#include "tp1.h"
bool BoundingBox::AABBDetection(const Shape& shape1, const Shape& shape2){

	std::array<vec3, 2> b1 = shape1.GetBB().GetAABB();
	std::array<vec3, 2> b2 = shape2.GetBB().GetAABB();

	return(b1[0].x > b2[1].x &&
		b1[1].x < b2[0].x &&
		b1[0].y > b2[1].y &&
		b1[1].y < b2[0].y &&
		b1[0].z > b2[1].z &&
		b1[1].z < b2[0].z);

}
bool BoundingBox::OBBDetection(const Shape& shape1, const Shape& shape2){

	//HYPERPLANE SEPARATION THEOREM (HST)
	//algorithme emprunte du livre 
	//
	//*****************************************************************************************************
	//Ericson, Christer, "Real-Time Collision Detection", Sony Computer Entertainment America, 2005, p.103
	//*****************************************************************************************************
	//
	//Lalgorithme consiste a utiliser les axes des boites 
	//orientees ainsi que leurs produits vectoriels pour
	//projeter leurs points sur les 15 axes obtenus (3+3+3x3) 
	//et determiner si il y a un espace entre 
	//les points projetes, et donc entre les deux boites.
	//S'il y a un espace, on peut tout de suite retourner faux 
	//puisque cela qu'un plan peut s'infiltrer entre les deux boites
	//et donc qu'il n'y a pas de collisions.
	//
	//Pour plus d'information: http://en.wikipedia.org/wiki/Hyperplane_separation_theorem

	BoundingBox a = shape1.GetBB();
	BoundingBox b = shape2.GetBB();
	float ra, rb;
	mat3 R, AbsR;
	// Compute rotation matrix expressing b in a’s coordinate frame
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			R[i][j] = dot(a.u[i], b.u[j]);
		}

	}


	// Compute translation vector t
	vec3 t = b.c - a.c;
	// Bring translation into a’s coordinate frame
	//ERRATA
	t = vec3(dot(t, a.u[0]), dot(t, a.u[1]), dot(t, a.u[2]));

	//t = vec3(dot(t, a.u[0]), dot(t, a.u[2]), dot(t, a.u[2]));

	// Compute common subexpressions. Add in an epsilon term to
	// counteract arithmetic errors when two edges are parallel and
	// their cross product is (near) null (see text for details)
	for (int i = 0; i < 3; i++)
	for (int j = 0; j < 3; j++)
		AbsR[i][j] = abs(R[i][j]) + epsilon<double>();
	// Test axes L = A0, L = A1, L = A2
	for (int i = 0; i < 3; i++) {
		ra = a.e[i];
		rb = b.e[0] * AbsR[i][0] + b.e[1] * AbsR[i][1] + b.e[2] * AbsR[i][2];
		if (abs(t[i]) > ra + rb) return 0;
	}
	// Test axes L = B0, L = B1, L = B2
	for (int i = 0; i < 3; i++) {
		ra = a.e[0] * AbsR[0][i] + a.e[1] * AbsR[1][i] + a.e[2] * AbsR[2][i];
		rb = b.e[i];
		if (abs(t[0] * R[0][i] + t[1] * R[1][i] + t[2] * R[2][i]) > ra + rb) return 0;
	}
	// Test axis L = A0 x B0
	ra = a.e[1] * AbsR[2][0] + a.e[2] * AbsR[1][0];
	rb = b.e[1] * AbsR[0][2] + b.e[2] * AbsR[0][1];
	if (abs(t[2] * R[1][0] - t[1] * R[2][0]) > ra + rb) return 0;
	// Test axis L = A0 x B1
	ra = a.e[1] * AbsR[2][1] + a.e[2] * AbsR[1][1];
	rb = b.e[0] * AbsR[0][2] + b.e[2] * AbsR[0][0];
	if (abs(t[2] * R[1][1] - t[1] * R[2][1]) > ra + rb) return 0;
	// Test axis L = A0 x B2
	ra = a.e[1] * AbsR[2][2] + a.e[2] * AbsR[1][2];
	rb = b.e[0] * AbsR[0][1] + b.e[1] * AbsR[0][0];
	if (abs(t[2] * R[1][2] - t[1] * R[2][2]) > ra + rb) return 0;
	// Test axis L = A1 x B0
	ra = a.e[0] * AbsR[2][0] + a.e[2] * AbsR[0][0];
	rb = b.e[1] * AbsR[1][2] + b.e[2] * AbsR[1][1];
	if (abs(t[0] * R[2][0] - t[2] * R[0][0]) > ra + rb) return 0;
	// Test axis L = A1 x B1
	ra = a.e[0] * AbsR[2][1] + a.e[2] * AbsR[0][1];
	rb = b.e[0] * AbsR[1][2] + b.e[2] * AbsR[1][0];
	if (abs(t[0] * R[2][1] - t[2] * R[0][1]) > ra + rb) return 0;
	// Test axis L = A1 x B2
	ra = a.e[0] * AbsR[2][2] + a.e[2] * AbsR[0][2];
	rb = b.e[0] * AbsR[1][1] + b.e[1] * AbsR[1][0];
	if (abs(t[0] * R[2][2] - t[2] * R[0][2]) > ra + rb) return 0;
	// Test axis L = A2 x B0
	ra = a.e[0] * AbsR[1][0] + a.e[1] * AbsR[0][0];
	rb = b.e[1] * AbsR[2][2] + b.e[2] * AbsR[2][1];
	if (abs(t[1] * R[0][0] - t[0] * R[1][0]) > ra + rb) return 0;
	// Test axis L = A2 x B1
	ra = a.e[0] * AbsR[1][1] + a.e[1] * AbsR[0][1];
	rb = b.e[0] * AbsR[2][2] + b.e[2] * AbsR[2][0];
	if (abs(t[1] * R[0][1] - t[0] * R[1][1]) > ra + rb) return 0;
	// Test axis L = A2 x B2
	ra = a.e[0] * AbsR[1][2] + a.e[1] * AbsR[0][2];
	rb = b.e[0] * AbsR[2][1] + b.e[1] * AbsR[2][0];
	if (abs(t[1] * R[0][2] - t[0] * R[1][2]) > ra + rb) return 0;
	// Since no separating axis is found, the OBBs must be intersecting
	return 1;

}
BoundingBox::BoundingBox(){
	set = 0;
}
BoundingBox::BoundingBox(const std::array<vec3, 2>& arr){
	set = 1;
	
	//lorsque l'on est en face du plan y z
	//f: front / r:rear
	//t: top / b:bottom
	//r: right / l:left
	vec3 corner_ftr{ arr[0].x, arr[0].y, arr[0].z };//0
	vec3 corner_rbl{ arr[1].x, arr[1].y, arr[1].z };//1
	vec3 corner_fbr{ corner_ftr.x, corner_rbl.y, corner_ftr.z };//2
	vec3 corner_ftl{ corner_ftr.x, corner_ftr.y, corner_rbl.z };//3
	vec3 corner_fbl{ corner_ftr.x, corner_rbl.y, corner_rbl.z };//4
	vec3 corner_rtr{ corner_rbl.x, corner_ftr.y, corner_ftr.z };//5
	vec3 corner_rtl{ corner_rbl.x, corner_ftr.y, corner_rbl.z };//6
	vec3 corner_rbr{ corner_rbl.x, corner_rbl.y, corner_ftr.z };//7

	init_points = { { corner_ftr, corner_rbl, corner_fbr, corner_ftl, corner_fbl, corner_rtr, corner_rtl, corner_rbr } };
	points = init_points;
	SetCenter();
	SetNormals();
	SetExtents();
	SetAABB();
}bool BoundingBox::IsSet(){
	return set;
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
	u.at(0) = normalize(points.at(4) - points.at(1)); //axe des x
	u.at(1) = normalize(points.at(6) - points.at(1)); //axe des y
	u.at(2) = normalize(points.at(7) - points.at(1)); //axe des z
	
	
}
void BoundingBox::SetCenter(){
	auto resultX = std::minmax_element(points.begin(), points.end(), [](const vec3& lhs, const vec3& rhs) {
		return lhs.x < rhs.x;
	});
	auto resultY = std::minmax_element(points.begin(), points.end(), [](const vec3& lhs, const vec3& rhs) {
		return lhs.y < rhs.y;
	});
	auto resultZ = std::minmax_element(points.begin(), points.end(), [](const vec3& lhs, const vec3& rhs) {
		return lhs.z < rhs.z;
	});
	c.x = resultX.first->x + (resultX.second->x - resultX.first->x) / 2;
	c.y = resultY.first->y + (resultY.second->y - resultY.first->y) / 2;
	c.z = resultZ.first->z + (resultZ.second->z - resultZ.first->z) / 2;
}
void BoundingBox::SetExtents(){
	e.at(0) = glm::length(points.at(4) - points.at(1))/2; //fbl-rbl
	e.at(1) = glm::length(points.at(6) - points.at(1))/2; //axe des y
	e.at(2) = glm::length(points.at(7) - points.at(1))/2; //axe des z
}

void BoundingBox::print(std::string name){
	std::cout << name << std::endl;
	std::cout << "center is " << c.x << "," << c.y << "," << c.z << "\n";
	std::cout << "normals are \n" << u[0].x << "," << u[0].y << "," << u[0].z << "\n" << u[1].x << "," << u[1].y << "," << u[1].z << "\n" << u[2].x << "," << u[2].y << "," << u[2].z << "\n";
	bool test = false;
	float scal = dot(u[0], u[1]);
	std::cout << "first dot product " << scal << "\n";

	scal = dot(u[0], u[2]);
	std::cout << "second dot product " << scal << "\n";

	scal = dot(u[1], u[2]);
	std::cout << "third dot product " << scal << "\n";

	std::cout << "extents are " << e[0] << "," << e[1] << "," << e[2] << "\n";
	for (int i = 0; i < 8; i++){

		printf("%1.2f , %1.2f, %1.2f\n", points[i].x, points[i].y, points[i].z);
	}
	printf("\n");
}
BoundingBox::~BoundingBox(){

}