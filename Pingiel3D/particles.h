
#define MAX_PARTICLES   10000  

typedef struct                      // Create A Structure For Particle
{
	
	bool fresh;
	bool    active;                 // Active (Yes/No)
	float   life;                   // Particle Life
	float   fade;                   // Fade Speed
	float   r;                  // Red Value
	float   g;                  // Green Value
	float   b;                  // Blue Value
	float   x;                  // X Position
	float   y;                  // Y Position
	float   z;                  // Z Position
	float   xi;                 // X Direction
	float   yi;                 // Y Direction
	float   zi;                 // Z Direction
	float   xg;                 // X Gravity
	float   yg;                 // Y Gravity
	float   zg;                 // Z Gravity
}
particles;

class genCzastek
{
public:
	genCzastek();
	void rysuj( double x, double z,bool tak);
private:
	particles* particle;
	
	float   xspeed;             // Base X Speed (To Allow Keyboard Direction Of Tail)
	float   yspeed;             // Base Y Speed (To Allow Keyboard Direction Of Tail)
	float   zoom;
	GLuint  loop;               // Misc Loop Variable
};