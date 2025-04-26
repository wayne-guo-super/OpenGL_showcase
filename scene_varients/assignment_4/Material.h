#ifndef MATERIAL_H
#define MATERIAL_H

class HitResult;

class ReflectResult
{
public:
    Ray m_ray;
    Vector3D m_color;
};

class Material
{
public:
    Vector3D m_color;
    virtual ReflectResult reflect(Ray& ray, HitResult& hit) = 0;
};


class Diffuse : public Material
{
public:
    Diffuse(const Vector3D& color)
    {
        m_color = color;
    };
    
    virtual ReflectResult reflect(Ray& ray, HitResult& hit) override
    {
        ReflectResult res;
        //TODO: 4. generate one scattered ray and assign it to res.m_ray
        Vector3D scatter_direction = normalize(hit.m_hitNormal + Vector3D::random());
        res.m_ray = Ray(hit.m_hitPos, scatter_direction);
        
        res.m_color = m_color;
        return res;
    }
};


class Specular : public Material
{
public:
    Specular(const Vector3D& color)
    {
        m_color = color;
    }
    
    virtual ReflectResult reflect(Ray& ray, HitResult& hit) override
    {
        ReflectResult res;
        //TODO: 5. generate one mirrored ray and assign it to res.m_ray
        // Calculate the reflected ray direction using the reflection formula
        //Vector3D incident_dir = normalize(ray.direction());
        //Vector3D reflected_dir = reflect(incident_dir, hit.m_hitNormal);

        // Set the reflected ray in the ReflectResult
        //res.m_ray = Ray(hit.m_hitPos, reflected_dir);

        res.m_color = m_color;
        return res;
    }
};
#endif
