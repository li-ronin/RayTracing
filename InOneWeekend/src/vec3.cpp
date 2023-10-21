#include "vec3.h"

double Vec3::getX() const {
    return e[0];
}
double Vec3::getY() const {
    return e[1];
}
double Vec3::getZ() const {
    return e[2];
}

double Vec3::operator[](size_t i) const {
    if(i>=3)return -1.0;
    return e[i];
}
double& Vec3::operator[](size_t i) {
    return e[i];
}

Vec3& Vec3::Add(const Vec3& v) {
    this->e[0] += v.e[0];
    this->e[1] += v.e[1];
    this->e[2] += v.e[2];
    return *this;
}
Vec3& Vec3::Sub(const Vec3& v){
    this->e[0] -= v.e[0];
    this->e[1] -= v.e[1];
    this->e[2] -= v.e[2];
    return *this;
}
Vec3& Vec3::Multiply(double d){
    this->e[0] *= d;
    this->e[1] *= d;
    this->e[2] *= d;
    return *this;
}
Vec3& Vec3::Divide(double d){
    this->e[0] /= d;
    this->e[1] /= d;
    this->e[2] /= d;
    return *this;
}
Vec3& Vec3::operator+=(const Vec3 &v) {
    return this->Add(v);
}
Vec3& Vec3::operator-=(const Vec3 &v) {
    return this->Sub(v);
}
Vec3& Vec3::operator*=(double d) {
    return this->Multiply(d);
}
Vec3& Vec3::operator/=(double d) {
    return this->Divide(d);
}

Vec3 Vec3::operator+(const Vec3 &v)const {
    return Vec3{this->e[0]+v.e[0], this->e[1]+v.e[1], this->e[2]+v.e[2]};
}
Vec3 Vec3::operator-(const Vec3 &v)const {
    return Vec3{this->e[0]-v.e[0], this->e[1]-v.e[1], this->e[2]-v.e[2]};
}
Vec3 Vec3::operator*(double d)const {
    return Vec3{this->e[0]*d, this->e[1]*d, this->e[2]*d};
}
Vec3 Vec3::operator/(double d)const {
    return Vec3{this->e[0]/d, this->e[1]/d, this->e[2]/d};
}

std::ostream& operator<<(std::ostream& os, const Vec3& vec)
{
	os << "[" << vec.e[0] << ", " << vec.e[1] <<", " << vec.e[2] << "]\n";
	return os;
}

double Vec3::dot(const Vec3 &v) {
    return this->e[0]*v.e[0] + this->e[1]*v.e[1] + this->e[2]*v.e[2];
}

void Vec3::write_color(std::ostream &out) {
    out<<static_cast<int>(255.99*e[0])<<" "
       <<static_cast<int>(255.99*e[1])<<" "
       <<static_cast<int>(255.99*e[2])<<"\n";
}