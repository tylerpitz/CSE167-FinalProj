#include "Material.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

Material::Material()
{
    //Material setup goes hurr
    ambientColor = Color::ambientMaterialDefault();
    diffuseColor = Color::diffuseMaterialDefault();
    specularColor = Color::specularMaterialDefault();
    emissionColor = Color::emissionMaterialDefault();
    shininess = 10.0;
    
    //Set the initial color to a random pastel color
    //Can be removed once materials are implemented
    color = Color::randomPastel();
}

Material::~Material()
{
    //Delete any dynamically allocated memory/objects here
}

void Material::apply(void)
{
    //Set the material properties for ambient, diffuse, specular, emission, and shininess
    //Hint: Lookup how glMaterialfv works
    
	float mat[4];

	mat[3] = 1.0;
	mat[0] = ambientColor[0];
	mat[1] = ambientColor[1];
	mat[2] = ambientColor[2];
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
	mat[0] = diffuseColor[0];
	mat[1] = diffuseColor[1];
	mat[2] = diffuseColor[2];
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
	mat[0] = specularColor[0];
	mat[1] = specularColor[1];
	mat[2] = specularColor[2];
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat);
	mat[0] = emissionColor[0];
	mat[1] = emissionColor[1];
	mat[2] = emissionColor[2];
	glMaterialfv(GL_FRONT, GL_EMISSION, mat);

	glMaterialf(GL_FRONT, GL_SHININESS, shininess);

    //Set the color property (can be removed once materials are implemented)
    //Used for projects 1, 2, and 3
    //glColor3fv(color.ptr());
}



