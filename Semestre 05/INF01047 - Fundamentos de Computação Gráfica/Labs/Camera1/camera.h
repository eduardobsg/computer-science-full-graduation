#include <GL/glut.h>

#define PI 3.1415265359


typedef struct _Vector3D  
{
	GLfloat x, y, z;
} Vector3D;


class Camera
{
	private:
		Vector3D Position;
		Vector3D ViewDir;		
		bool ViewDirChanged;
		GLfloat RotatedX, RotatedY, RotatedZ;	
		
	public:
		Camera();
		void GetViewDir(void);
		void Move(Vector3D);
		void MoveForwards(GLfloat);
		void Render(void);	
		void RotateX(GLfloat);
		void RotateY(GLfloat);
		void RotateZ(GLfloat);
		void StrafeRight(GLfloat);
		Vector3D ReturnVector3D(GLfloat, GLfloat, GLfloat);
		void AddVector3DToVector3D(Vector3D *, Vector3D *);	
};


