#include "Pingiel3D.h"

genCzastek::genCzastek()
{
		
		particle = new particles[MAX_PARTICLES];
		for (loop = 0; loop<MAX_PARTICLES; loop++)                   // Initialize All The Textures
		{
			particle[loop].fresh = false;
			particle[loop].active = true;                 // Make All The Particles Active
			particle[loop].life = 3.0f;
			particle[loop].fade = float(rand() % 100) / 1000.0f + 0.003f;
			particle[loop].r = 1.0;          // Select Red From Color Table
			particle[loop].g = rand()+0.5;            // Select Green From Color Table
			particle[loop].b = 0;
			particle[loop].xi = float((rand() % 50) - 26.0f)*25.0f;       // Random Speed On X Axis
			particle[loop].yi = float((rand() % 50) - 25.0f)*50.0f;       // Random Speed On Y Axis
			particle[loop].zi = float((rand() % 50) - 25.0f)*150.0f;       // Random Speed On Z Axis
			particle[loop].xg = (float((rand() % 2)) - 1)*0.5;                 // Set Horizontal Pull To Zero
			particle[loop].yg = 0.3f;                    // Set Vertical Pull Downward
			particle[loop].zg = -1.5f;                     // Set Pull On Z Axis To Zero
		}
	}


void	genCzastek::rysuj( double dx, double dz, bool tak)
	{
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
		for (loop = 0; loop < MAX_PARTICLES; loop++)                 
		{
			particle[loop].active = tak;
			if (1)                  
			{

				if (particle[loop].fresh)
				{
					
					particle[loop].x = dx;       
					particle[loop].z = dz;
					particle[loop].fresh = false;
					
				}
				
					float x = particle[loop].x;               
					float y = particle[loop].y;               
					float z = particle[loop].z;
				
					glColor4f(particle[loop].r, particle[loop].g, particle[loop].b, particle[loop].life);
				if (particle[loop].life>0)
				{
					glPushMatrix();
					glTranslated(cos(z), -sin(x), 0);
					glBegin(GL_TRIANGLE_STRIP);			
					
					glVertex3f(x + 0.1f, y + 0.1f, z); // Top Right
					glVertex3f(x - 0.1f, y + 0.1f, z); // Top Left
					glVertex3f(x + 0.1f, y - 0.1f, z); // Bottom Right
					glVertex3f(x - 0.1f, y - 0.1f, z); // Bottom Left
					glEnd();
					
					glPopMatrix();
				}
				particle[loop].x += particle[loop].xi / ( 1000);    // Move On The X Axis By X Speed
				particle[loop].y += particle[loop].yi / ( 1000);    // Move On The Y Axis By Y Speed
				particle[loop].z += particle[loop].zi / ( 500);    // Move On The Z Axis By Z Speed
				particle[loop].xi += particle[loop].xg;           // Take Pull On X Axis Into Account
				particle[loop].yi += particle[loop].yg;           // Take Pull On Y Axis Into Account
				particle[loop].zi += particle[loop].zg;           // Take Pull On Z Axis Into Account

				particle[loop].r = 1.0;           // Select Red From Color Table
				particle[loop].g = (static_cast<double>(rand()) / (RAND_MAX)) + 0.4;         // Select Green From Color Table
				particle[loop].b = (static_cast<double>(rand()) / (RAND_MAX));
				particle[loop].life -= particle[loop].fade;
				if (particle[loop].life < 0.0f && particle[loop].active)                    // If Particle Is Burned Out
				{
					particle[loop].fresh = true;
					particle[loop].xg = (float((rand() % 2)) - 1)*0.5;
					particle[loop].life = 3.0f;               // Give It New Life
					particle[loop].fade = float(rand() % 100) / 1000.0f + 0.003f;
					particle[loop].x = float(rand() % 10)-5;                  // Center On X Axis
					particle[loop].y = 0.0f;                  // Center On Y Axis
					particle[loop].z = 0.0f;
					particle[loop].xi = xspeed + float((rand() % 60) - 32.0f);  // X Axis Speed And Direction
					particle[loop].yi = yspeed + float((rand() % 60) - 30.0f);  // Y Axis Speed And Direction
					particle[loop].zi = float((rand() % 60) - 30.0f);
					particle[loop].r = 1.0;
					particle[loop].g = (static_cast<double>(rand()) / (RAND_MAX))+0.8;
					particle[loop].b = 0;
				}


			}
		}
		glColor4f(1, 1, 1, 1);
	
	}
