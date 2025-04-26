#ifndef SPHERE_H
#define SPHERE_H

#include <memory>

using namespace std;
class Material;

class HitResult {
public:
    HitResult() { m_isHit = false; };
    bool m_isHit;
    Vector3D m_hitPos;
    Vector3D m_hitNormal;
    shared_ptr<Material> m_hitMaterial;
    float m_t;
};


class Sphere {
    
public:
    Sphere() {}
    Sphere(Vector3D center, float r, shared_ptr<Material> m)
    {
        m_center = center;
        m_radius = r;
        m_pMaterial = m;
    }
    HitResult hit(Ray& r, float min_t, float max_t);

    public:
    Vector3D m_center;
    float m_radius;
    shared_ptr<Material> m_pMaterial;
};


//test if ray hits this sphere within range min_t and max_t
HitResult Sphere::hit(Ray& ray, float min_t, float max_t)
{
    /*HitResult hit_result;
     TODO: 2. compute ray hit information on the sphere

    
    // and fill in hit result
    hit_result.m_isHit = ...;
    hit_result.m_t = ...;
    hit_result.m_hitPos = ...;
    hit_result.m_hitNormal = ...;
    hit_result.m_hitMaterial = ...;
    return hit_result;*/
    
    HitResult hit_result;

    Vector3D oc = ray.origin() - m_center;
    float a = dot(ray.direction(), ray.direction());
    float b = dot(oc, ray.direction());
    float c = dot(oc, oc) - m_radius * m_radius;
    float discriminant = b * b - a * c;

    if (discriminant > 0)
    {
        // Ray intersects with the sphere
        float temp = (-b - sqrt(discriminant)) / a;
        if (temp < max_t && temp > min_t)
        {
            hit_result.m_isHit = true;
            hit_result.m_t = temp;
            hit_result.m_hitPos = ray.at(temp);
            hit_result.m_hitNormal = normalize(hit_result.m_hitPos - m_center);
            hit_result.m_hitMaterial = m_pMaterial;
            return hit_result;
        }

        temp = (-b + sqrt(discriminant)) / a;
        if (temp < max_t && temp > min_t)
        {
            hit_result.m_isHit = true;
            hit_result.m_t = temp;
            hit_result.m_hitPos = ray.at(temp);
            hit_result.m_hitNormal = normalize(hit_result.m_hitPos - m_center);
            hit_result.m_hitMaterial = m_pMaterial;
            return hit_result;
        }
    }

    // No intersection
    return hit_result;
}

#endif

