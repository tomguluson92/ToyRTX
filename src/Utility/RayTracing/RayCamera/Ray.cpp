#include <RayTracing/Ray.h>

using namespace glm;
using namespace RayTracing;

const float Ray::tMin = 10e-4;

Ray::Ray(const vec3 & origin, const vec3 & dir){
	Init(origin, dir);
}

vec3 Ray::operator ()(float t) const {
	return origin + t * dir;
}

vec3 Ray::At(float t) const {
	return origin + t * dir;
}

void Ray::Init(const glm::vec3 & origin, const glm::vec3 & dir) {
	this->origin = origin;
	this->dir = dir;
	color = vec3(1.0f);
	tMax = FLT_MAX;
}

void Ray::Update(const vec3 & origin, const vec3 & dir, const vec3 & attenuation) {
	this->origin = origin;
	this->dir = dir;
	color *= attenuation;
	tMax = FLT_MAX;
}


void Ray::SetLightColor(const glm::vec3 & lightColor) {
	origin = vec3(0);
	dir = vec3(0);
	color *= lightColor;
	tMax = 0;
}

void Ray::Transform(const glm::mat4 & transform) {
	dir = mat3(transform) * dir;
	auto originQ = transform * vec4(origin, 1.0f);
	origin = vec3(originQ) / originQ.w;
}

Ray::Ptr Ray::GenCopy() const {
	auto ray = ToPtr(new Ray);
	CopyTo(ray);
	return ray;
}

void Ray::CopyTo(Ray::Ptr ray) const{
	ray->origin = origin;
	ray->dir = dir;
	ray->color = color;
	ray->tMax = tMax;
}