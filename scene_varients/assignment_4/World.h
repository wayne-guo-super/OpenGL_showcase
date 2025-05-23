#ifndef WORLD_H
#define WORLD_H

#include <vector>

#include "Sphere.h"
#include "Material.h"

using namespace std;
class World
{
public:
    std::vector<shared_ptr<Sphere>> m_spheres;
    
    World() {}
    HitResult hit(Ray& ray, float min_t, float max_t);
    
    void generate_scene_one_diffuse();
    void generate_scene_one_specular();
    void generate_scene_multi_diffuse();
    void generate_scene_multi_specular();
    void generate_scene_all();
};


HitResult World::hit(Ray& ray, float min_t, float max_t)
{
    HitResult hit_result;
    
    // TODO: 3. loop over each sphere in m_spheres
    // call sphere->hit(...)
    // hit_result should record the nearest hit
    
    // Set an initial maximum hit parameter
        float closest_t = max_t;

        // Loop over each sphere in m_spheres
        for (const auto& sphere : m_spheres)
        {
            // Call sphere->hit(...)
            HitResult temp_result = sphere->hit(ray, min_t, closest_t);

            // Check if there is a hit and if it is the closest so far
            if (temp_result.m_isHit && temp_result.m_t < closest_t)
            {
                // Update hit_result with the information from the current sphere
                hit_result = temp_result;

                // Update the closest_t to the current hit parameter
                closest_t = temp_result.m_t;
            }
        }
    
    return hit_result;
}

void World::generate_scene_one_diffuse()
{
    m_spheres.clear();
    
    auto material_diffuse = make_shared<Diffuse>(Vector3D(0.3, 0.4, 0.5));
    m_spheres.push_back(make_shared<Sphere>(Vector3D(4, 1, 0), 1.0, material_diffuse));
    
    //floor
    auto material_floor = make_shared<Diffuse>(Vector3D(0.5, 0.5, 0.5));
    m_spheres.push_back(make_shared<Sphere>(Vector3D(0,-2000,0), 2000, material_floor));
}

void World::generate_scene_one_specular()
{
    m_spheres.clear();
    
    auto material_diffuse = make_shared<Specular>(Vector3D(1, 1, 1));
    m_spheres.push_back(make_shared<Sphere>(Vector3D(4, 1, 0), 1.0, material_diffuse));
    
    //floor
    auto material_floor = make_shared<Diffuse>(Vector3D(0.5, 0.5, 0.5));
    m_spheres.push_back(make_shared<Sphere>(Vector3D(0,-2000,0), 2000, material_floor));
}

void World::generate_scene_multi_diffuse()
{
    m_spheres.clear();
    
    for (int row = -3; row < 3; ++row)
    {
        for (int col = -3; col < 3; ++col)
        {
            float radius = random_float(0.2, 0.8);
            Vector3D center(3*row + 0.5*random_float(), radius, 3*col + 0.5*random_float());
            shared_ptr<Material> sphere_material;
            
            Vector3D color = Vector3D::random() * Vector3D::random();
            sphere_material = make_shared<Diffuse>(color);
            m_spheres.push_back(make_shared<Sphere>(center, radius, sphere_material));
        }
    }
    
    //floor
    auto material_floor = make_shared<Diffuse>(Vector3D(0.5, 0.5, 0.5));
    m_spheres.push_back(make_shared<Sphere>(Vector3D(0,-2000,0), 2000, material_floor));
}

void World::generate_scene_multi_specular()
{
    m_spheres.clear();
    
    for (int row = -3; row < 3; ++row)
    {
        for (int col = -3; col < 3; ++col)
        {
            float radius = random_float(0.2, 0.8);
            Vector3D center(3*row + 0.5*random_float(), radius, 3*col + 0.5*random_float());
            shared_ptr<Material> sphere_material;
            
            Vector3D color = Vector3D::random(0.3, 1);
            sphere_material = make_shared<Specular>(color);
            m_spheres.push_back(make_shared<Sphere>(center, radius, sphere_material));
        }
    }
    
    //floor
    auto material_floor = make_shared<Diffuse>(Vector3D(0.5, 0.5, 0.5));
    m_spheres.push_back(make_shared<Sphere>(Vector3D(0,-2000,0), 2000, material_floor));
    
}
void World::generate_scene_all()
{
    m_spheres.clear();
    for (int row = -5; row < 10; ++row)
    {
        for (int col = -5; col < 5; ++col)
        {
            float radius = random_float(0.2, 0.5);
            Vector3D center(1.5*row + 0.5*random_float(), radius, 1.5*col + 0.5*random_float());
            
            bool isDiffuse = random_float() <= 0.6;
            Vector3D color = isDiffuse ? Vector3D::random() * Vector3D::random() : Vector3D::random(0.5, 1);
            
            shared_ptr<Material> material;
            if(isDiffuse)
                material = make_shared<Diffuse>(color);
            else
                material = make_shared<Specular>(color);
            m_spheres.push_back(make_shared<Sphere>(center, radius, material));
        }
    }
    
    //floor
    auto material_floor = make_shared<Diffuse>(Vector3D(0.5, 0.5, 0.5));
    m_spheres.push_back(make_shared<Sphere>(Vector3D(0,-2000,0), 2000, material_floor));
}


#endif
