#ifndef __MODULE_RENDERER__
#define __MODULE_RENDERER__

#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "Light.h"

#include "MathGeoLib/MathBuildConfig.h"
#include "MathGeoLib/MathGeoLib.h"

#define MAX_LIGHTS 8

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

	void OnResize(int width, int height);

	// for mesh ----
	void DrawMesh(MeshData _mesh, math::float4x4 trans_mat, uint _name_id);

public:
	Light lights[MAX_LIGHTS];
	SDL_GLContext context;
	mat3x3 NormalMatrix;
	mat4x4 ModelMatrix, ViewMatrix, ProjectionMatrix;
};
#endif // !__MODULE_RENDERER__