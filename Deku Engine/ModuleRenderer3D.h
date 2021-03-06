#ifndef __MODULE_RENDERER3D_H__
#define __MODULE_RENDERER3D_H__

#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "Light.h"
#include "MathGeoLib/src/MathGeoLib.h"

#define MAX_LIGHTS 8

struct MeshData;
namespace math { class float4x4; class AABB; }

class ModuleRenderer3D : public Module
{
public:
	ModuleRenderer3D(Application* app, bool start_enabled = true);
	~ModuleRenderer3D();

	bool Init();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();
	
	void RenderMesh(MeshData mesh, math::float4x4 transform, uint tex_id, bool mat_enable);
	void RenderBBoxDebug(math::AABB bbox);
	void RenderFrustum(math::Frustum frustum);

	void OnResize(int width, int height);

public:
	uint my_id = 0;
	Light lights[MAX_LIGHTS];
	SDL_GLContext context;
	mat3x3 NormalMatrix;
	mat4x4 ModelMatrix, ViewMatrix, ProjectionMatrix;
};
#endif // !__MODULE_RENDERER3D_H__