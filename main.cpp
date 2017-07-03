/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: lukasz
 *
 * Created on 7 października 2016, 15:50
 */

#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <stdio.h>
#include <ctime>
#include <cstdlib>

typedef float point2[2];
typedef float point3[3];

static GLfloat 	viewer[3];
static GLfloat 	radius 				= 20;
static GLfloat 	fi 				= 0;
static GLfloat 	theta 				= M_PI / 2;
static GLfloat 	spin_theta 			= 0;
static GLfloat 	theta_pos_old    		= 0;    // poprzednia pozycja kursora myszy
static GLfloat 	delta_theta             	= 0;    // różnica pomiędzy pozycją bieżącą i poprzednią kursora myszy
static GLfloat 	fi_pos_old 			= 0;
static GLfloat 	delta_fi 			= 0;
static GLint 	status 				= 0;    // stan klawiszy myszy
                               				// 0 - nie naciśnięto żadnego klawisza
                               				// 1 - naciśnięty został lewy klawisz
							// 2 - naciśnięty został prawy klawisz
static int      lights				= 0;	// stan oswietlenia
                                                        // 0 - oswietlenie wylaczone
							// 1 - oswietlenie białe wlaczone
							// 2 - oswietlenie czerwone włączone
							// 3 - oswietlenie niebieskie właczone
							// 4 - oswietlenie czerwone i niebieskie wlaczone
static int	active				= 0;	// numer aktualnie obracanego oświetlenia
static GLfloat	l0_radius			= 10;
static GLfloat	l0_fi				= 0;
static GLfloat	l0_theta			= M_PI / 2;
static GLfloat	l0_theta_pos_old                = 0;
static GLfloat	l0_delta_theta  		= 0;
static GLfloat	l0_fi_pos_old           	= 0;
static GLfloat	l0_delta_fi			= 0;

static GLfloat	l1_radius			= 10;
static GLfloat	l1_fi				= 0;
static GLfloat	l1_theta			= M_PI / 2;
static GLfloat	l1_theta_pos_old                = 0;
static GLfloat	l1_delta_theta          	= 0;
static GLfloat	l1_fi_pos_old                   = 0;
static GLfloat	l1_delta_fi			= 0;

static GLfloat	l2_radius			= 10;
static GLfloat	l2_fi				= 0;
static GLfloat	l2_theta			= M_PI / 2;
static GLfloat	l2_theta_pos_old                = 0;
static GLfloat	l2_delta_theta                  = 0;
static GLfloat	l2_fi_pos_old                   = 0;
static GLfloat	l2_delta_fi			= 0;

static int      N 				= 100;

                                                                // model wyswietlania
int model                                       = 1;            // 1 - punkty,
                                                        	// 2 - trojkaty,
                                                        	// 3 - wypenione trojkaty
                                                        	// 4 - wypełnione trojkaty z wektorami normalnymi
                                                        	// 5 - teksturowane trojkaty z wektorami normalnymi

using namespace std;

class Egg {

	private:
		point2  **pTab;
		point3  **tab;
		point3  **colors;
		int     r;
	public:
		Egg();
		Egg(int m);
		~Egg();
		void rysuj();
};

Egg::Egg() {

	r               = N;
	pTab 		= new point2* [r];
	tab 		= new point3* [r];
	colors		= new point3* [r];

	for (int i = 0; i < r; i++) {

		pTab[i] 	= new point2[r];
		tab[i]  	= new point3[r];
		colors[i]	= new point3[r];
	}

	for (int i = 0; i < r; i++) {
		for(int j = 0; j < r; j++) {

			pTab[i][j][0] = (float)i / r;
			pTab[i][j][1] = (float)j / r;

			colors[i][j][0] = float (rand() % 1000) / 1000;
			colors[i][j][1] = float (rand() % 1000) / 1000;
			colors[i][j][2] = float (rand() % 1000) / 1000;
		}
	}
	for (int i = 0; i < r; i++) {
		for(int j = 0; j < r; j++) {

			tab[i][j][0] = (-90*(pow(pTab[i][j][0], 5)) + 225*(pow(pTab[i][j][0], 4)) - 270*(pow(pTab[i][j][0], 3)) + 180*(pow(pTab[i][j][0], 2)) - 45*pTab[i][j][0]) * cos(M_PI * pTab[i][j][1]);
			tab[i][j][1] = (160*(pow(pTab[i][j][0], 4)) - 320*(pow(pTab[i][j][0], 3)) + 160*(pow(pTab[i][j][0], 2)));
			tab[i][j][2] = (-90*(pow(pTab[i][j][0], 5)) + 225*(pow(pTab[i][j][0], 4)) - 270*(pow(pTab[i][j][0], 3)) + 180*(pow(pTab[i][j][0], 2)) - 45*pTab[i][j][0]) * sin(M_PI * pTab[i][j][1]);
		}
	}
};

Egg::Egg(int m) {

	r		= m;
	pTab 		= new point2 *[r];
	tab 		= new point3 *[r];
	colors		= new point3 *[r];

	for (int i = 0; i < N; i++) {

		pTab[i] 	= new point2[r];
		tab[i]  	= new point3[r];
		colors[i]	= new point3[r];
	}

	for (int i = 0; i < r; i++) {
		for(int j = 0; j < r; j++) {

			pTab[i][j][0] = (float)i / r;
			pTab[i][j][1] = (float)j / r;

			colors[i][j][0] = float (rand() % 1000) / 1000;
			colors[i][j][1] = float (rand() % 1000) / 1000;
			colors[i][j][2] = float (rand() % 1000) / 1000;
		}
	}
	for (int i = 0; i < r; i++) {
		for(int j = 0; j < r; j++) {

			tab[i][j][0] = (-90*(pow(pTab[i][j][0], 5)) + 225*(pow(pTab[i][j][0], 4)) - 270*(pow(pTab[i][j][0], 3)) + 180*(pow(pTab[i][j][0], 2)) - 45*pTab[i][j][0]) * cos(M_PI * pTab[i][j][1]);
			tab[i][j][1] = (160*(pow(pTab[i][j][0], 4)) - 320*(pow(pTab[i][j][0], 3)) + 160*(pow(pTab[i][j][0], 2)));
			tab[i][j][2] = (-90*(pow(pTab[i][j][0], 5)) + 225*(pow(pTab[i][j][0], 4)) - 270*(pow(pTab[i][j][0], 3)) + 180*(pow(pTab[i][j][0], 2)) - 45*pTab[i][j][0]) * sin(M_PI * pTab[i][j][1]);
		}
	}
};

Egg::~Egg() {

	for (int i = 0; i < r; i++) {

		delete [] pTab[i];
		delete [] tab[i];
		delete [] colors[i];
	}

	delete [] pTab;
	delete [] tab;
	delete [] colors;

	pTab 	= NULL;
	tab	= NULL;
	colors	= NULL;
}

void Egg::rysuj() {

	point3	normal;
//	point3 	normal_end;
	GLfloat	length;
	float	x_u;
	float	x_v;
	float	y_u;
	float	y_v;
	float	z_u;
	float	z_v;

	switch (model) {

	case 1:

		for (int i = 0; i < r; i++) {
			for(int j = 0; j < r; j++) {

				glBegin(GL_POINTS);
					glColor3f(1.0f, 1.0f, 0.0f);
					glVertex3fv(tab[i][j]);
				glEnd();
			}
		}
		break;


	case 2:

		for (int i = 0; i < r; i++) {
			for(int j = 0; j < r; j++) {

				// linie pionowe
				glBegin(GL_LINES);
				glColor3f(0.0f, 1.0f, 0.0f);
					glVertex3fv(tab[i][j]);
					glVertex3fv(tab[(i + 1) % r][j]);
				glEnd();
				//linie ukośne
				glBegin(GL_LINES);
					if (((j + 1) != r) && ((i + 1) != r)) {
						glVertex3fv(tab[i + 1][j]);
						glVertex3fv(tab[i][j + 1]);
					}
					else {
//						glColor3f(0.0f, 1.0f, 1.0f);
						if (i > 0) {
							glVertex3fv(tab[i][j]);
							glVertex3fv(tab[r - i - 1][0]);
						}
					}
				glEnd();
				//linie poziome
				glBegin(GL_LINES);
				glColor3f(0.0f, 1.0f, 0.0f);
					if ((j + 1) == r) {
						if (i > 0) {
							glVertex3fv(tab[r - i][0]);
							glVertex3fv(tab[i][j]);
						}
					}
					else {
						glVertex3fv(tab[i][j + 1]);
						glVertex3fv(tab[i][j]);
					}
				glEnd();
			}
		}
		break;

	case 3:

		for (int i = 0; i < r; i++) {
			for(int j = 0; j < r; j++) {
				if ((j + 1) != r) {
					glBegin(GL_TRIANGLES);
						glColor3fv(colors[i][j]);
						glVertex3fv(tab[i][j]);
						glColor3fv(colors[(i + 1) % r][j]);
						glVertex3fv(tab[(i + 1) % r][j]);
						glColor3fv(colors[i][j + 1]);
						glVertex3fv(tab[i][j + 1]);
					glEnd();

					glBegin(GL_TRIANGLES);
						glColor3fv(colors[(i + 1) % r][j]);
						glVertex3fv(tab[(i + 1) % r][j]);
						glColor3fv(colors[(i + 1) % r][j + 1]);
						glVertex3fv(tab[(i + 1) % r][j + 1]);
						glColor3fv(colors[i][j + 1]);
						glVertex3fv(tab[i][j + 1]);
					glEnd();
				}
				else {
					if (i > 0) {
						glBegin(GL_TRIANGLES);
//							glColor3f(1.0f, 1.0f, 0.0f);
							glColor3fv(colors[i][j]);
							glVertex3fv(tab[i][j]);
							glColor3fv(colors[(i + 1) % r][j]);
							glVertex3fv(tab[(i + 1) % r][j]);
							glColor3fv(colors[r - i][0]);
							glVertex3fv(tab[r - i][0]);
						glEnd();
					}
					glBegin(GL_TRIANGLES);
//						glColor3f(0.0f, 0.0f, 1.0f);
						glColor3fv(colors[(i + 1) % r][j]);
						glVertex3fv(tab[(i + 1) % r][j]);
						glColor3fv(colors[(r - i) % r][0]);
						glVertex3fv(tab[(r - i) % r][0]);
						glColor3fv(colors[r - i - 1][0]);
						glVertex3fv(tab[r - i - 1][0]);
					glEnd();

				}
			}
		}
		break;

	case 4:

		for (int i = 0; i < r; i++) {
			for(int j = 0; j < r; j++) {

				x_u		= (-450 * pow(pTab[i][j][0], 4) + 900 * pow(pTab[i][j][0], 3) - 810 * pow(pTab[i][j][0], 2) + 360 * pTab[i][j][0] - 45) * cos(M_PI * pTab[i][j][1]);
				x_v             = M_PI * (90 * pow(pTab[i][j][0], 5) - 225 * pow(pTab[i][j][0], 4) + 270 * pow(pTab[i][j][0], 3) - 180 * pow(pTab[i][j][0], 2) + 45 * pTab[i][j][0]) * sin(M_PI * pTab[i][j][1]);
				y_u		= 640 * pow(pTab[i][j][0], 3) - 960 * pow(pTab[i][j][0], 2) + 320 * pTab[i][j][0];
				y_v		= 0;
				z_u		= (-450 * pow(pTab[i][j][0], 4) + 900 * pow(pTab[i][j][0], 3) - 810 * pow(pTab[i][j][0], 2) + 360 * pTab[i][j][0] - 45) * sin(M_PI * pTab[i][j][1]);
				z_v		= - M_PI * (90 * pow(pTab[i][j][0], 5) - 225 * pow(pTab[i][j][0], 4) + 270 * pow(pTab[i][j][0], 3) - 180 * pow(pTab[i][j][0], 2) + 45 * pTab[i][j][0]) * cos(M_PI * pTab[i][j][1]);

				normal[0] 	= y_u * z_v - z_u * y_v;
				normal[1]	= z_u * x_v - x_u * z_v;
				normal[2]	= x_u * y_v - y_u * x_v;
				length		= sqrt(pow(normal[0], 2) + pow(normal[1], 2) + pow(normal[2], 2));

				if (length == 0) {
					if (i == 0) normal[1] 	= -1;
					// zabezpieczenie przed dzieleniem przez zero
					length = 1;
				}

				if (i >= (r / 2)) {
					normal[0] *= -1;
					normal[1] *= -1;
					normal[2] *= -1;
				}

				normal[0] = normal[0] / length;
				normal[1] = normal[1] / length;
				normal[2] = normal[2] / length;

//				normal_end[0] 	= tab[i][j][0] + normal[0];
//				normal_end[1]	= tab[i][j][1] + normal[1];
//				normal_end[2]	= tab[i][j][2] + normal[2];

				if ((j + 1) != r) {
//					glColor3f(1.0f, 0.0f, 0.0f);
//					glBegin(GL_LINES);
//						glVertex3fv(tab[i][j]);
//						glVertex3fv(normal_end);
//					glEnd;
					glBegin(GL_TRIANGLES);
                                                // ustawienie koloru rysowania na bialy
						glColor3f(1.0f, 1.0f, 1.0f);
						glNormal3fv(normal);
						glVertex3fv(tab[i][j]);
						glVertex3fv(tab[(i + 1) % r][j]);
						glVertex3fv(tab[i][j + 1]);
					glEnd();

					x_u		= (-450 * pow(pTab[(i + 1) % r][j][0], 4) + 900 * pow(pTab[(i + 1) % r][j][0], 3) - 810 * pow(pTab[(i + 1) % r][j][0], 2) + 360 * pTab[(i + 1) % r][j][0] - 45) * cos(M_PI * pTab[(i + 1) % r][j][1]);
					x_v 	= M_PI * (90 * pow(pTab[(i + 1) % r][j][0], 5) - 225 * pow(pTab[(i + 1) % r][j][0], 4) + 270 * pow(pTab[(i + 1) % r][j][0], 3) - 180 * pow(pTab[(i + 1) % r][j][0], 2) + 45 * pTab[(i + 1) % r][j][0]) * sin(M_PI * pTab[(i + 1) % r][j][1]);
					y_u		= 640 * pow(pTab[(i + 1) % r][j][0], 3) - 960 * pow(pTab[(i + 1) % r][j][0], 2) + 320 * pTab[(i + 1) % r][j][0];
					y_v		= 0;
					z_u		= (-450 * pow(pTab[(i + 1) % r][j][0], 4) + 900 * pow(pTab[(i + 1) % r][j][0], 3) - 810 * pow(pTab[(i + 1) % r][j][0], 2) + 360 * pTab[(i + 1) % r][j][0] - 45) * sin(M_PI * pTab[(i + 1) % r][j][1]);
					z_v		= - M_PI * (90 * pow(pTab[(i + 1) % r][j][0], 5) - 225 * pow(pTab[(i + 1) % r][j][0], 4) + 270 * pow(pTab[(i + 1) % r][j][0], 3) - 180 * pow(pTab[(i + 1) % r][j][0], 2) + 45 * pTab[(i + 1) % r][j][0]) * cos(M_PI * pTab[(i + 1) % r][j][1]);

					normal[0] 	= y_u * z_v - z_u * y_v;
					normal[1]	= z_u * x_v - x_u * z_v;
					normal[2]	= x_u * y_v - y_u * x_v;
					length		= sqrt(pow(normal[0], 2) + pow(normal[1], 2) + pow(normal[2], 2));

					if (length == 0) {
						if (i == 0) normal[1] 	= -1;
                                                // zabezpieczenie przed dzieleniem przez zero
						length = 1;
					}

					if (i >= (r / 2)) {
						normal[0] *= -1;
						normal[1] *= -1;
						normal[2] *= -1;
					}

					normal[0] = normal[0] / length;
					normal[1] = normal[1] / length;
					normal[2] = normal[2] / length;

					glBegin(GL_TRIANGLES);
						glNormal3fv(normal);
						glVertex3fv(tab[(i + 1) % r][j]);
						glVertex3fv(tab[(i + 1) % r][j + 1]);
						glVertex3fv(tab[i][j + 1]);
					glEnd();
				}
				else {
					if (i > 0) {
						glBegin(GL_TRIANGLES);
							glNormal3fv(normal);
							glVertex3fv(tab[i][j]);
							glVertex3fv(tab[(i + 1) % r][j]);
							glVertex3fv(tab[r - i][0]);
						glEnd();
					}

					x_u		= (-450 * pow(pTab[(i + 1) % r][j][0], 4) + 900 * pow(pTab[(i + 1) % r][j][0], 3) - 810 * pow(pTab[(i + 1) % r][j][0], 2) + 360 * pTab[(i + 1) % r][j][0] - 45) * cos(M_PI * pTab[(i + 1) % r][j][1]);
					x_v 	= M_PI * (90 * pow(pTab[(i + 1) % r][j][0], 5) - 225 * pow(pTab[(i + 1) % r][j][0], 4) + 270 * pow(pTab[(i + 1) % r][j][0], 3) - 180 * pow(pTab[(i + 1) % r][j][0], 2) + 45 * pTab[(i + 1) % r][j][0]) * sin(M_PI * pTab[(i + 1) % r][j][1]);
					y_u		= 640 * pow(pTab[(i + 1) % r][j][0], 3) - 960 * pow(pTab[(i + 1) % r][j][0], 2) + 320 * pTab[(i + 1) % r][j][0];
					y_v		= 0;
					z_u		= (-450 * pow(pTab[(i + 1) % r][j][0], 4) + 900 * pow(pTab[(i + 1) % r][j][0], 3) - 810 * pow(pTab[(i + 1) % r][j][0], 2) + 360 * pTab[(i + 1) % r][j][0] - 45) * sin(M_PI * pTab[(i + 1) % r][j][1]);
					z_v		= - M_PI * (90 * pow(pTab[(i + 1) % r][j][0], 5) - 225 * pow(pTab[(i + 1) % r][j][0], 4) + 270 * pow(pTab[(i + 1) % r][j][0], 3) - 180 * pow(pTab[(i + 1) % r][j][0], 2) + 45 * pTab[(i + 1) % r][j][0]) * cos(M_PI * pTab[(i + 1) % r][j][1]);

					normal[0] 	= y_u * z_v - z_u * y_v;
					normal[1]	= z_u * x_v - x_u * z_v;
					normal[2]	= x_u * y_v - y_u * x_v;
					length		= sqrt(pow(normal[0], 2) + pow(normal[1], 2) + pow(normal[2], 2));

					if (length == 0) {
						if (i == 0) normal[1] 	= -1;
                                                // zabezpieczenie przed dzieleniem przez zero
						length = 1;
					}

					if (i >= (r / 2)) {
						normal[0] *= -1;
						normal[1] *= -1;
						normal[2] *= -1;
					}

					normal[0] = normal[0] / length;
					normal[1] = normal[1] / length;
					normal[2] = normal[2] / length;

					glBegin(GL_TRIANGLES);
						glNormal3fv(normal);
						glVertex3fv(tab[(i + 1) % r][j]);
						glVertex3fv(tab[(r - i) % r][0]);
						glVertex3fv(tab[r - i - 1][0]);
					glEnd();

				}
			}
		}
		break;

	case 5:

		for (int i = 0; i < r; i++) {
			for(int j = 0; j < r; j++) {

				x_u		= (-450 * pow(pTab[i][j][0], 4) + 900 * pow(pTab[i][j][0], 3) - 810 * pow(pTab[i][j][0], 2) + 360 * pTab[i][j][0] - 45) * cos(M_PI * pTab[i][j][1]);
				x_v 	= M_PI * (90 * pow(pTab[i][j][0], 5) - 225 * pow(pTab[i][j][0], 4) + 270 * pow(pTab[i][j][0], 3) - 180 * pow(pTab[i][j][0], 2) + 45 * pTab[i][j][0]) * sin(M_PI * pTab[i][j][1]);
				y_u		= 640 * pow(pTab[i][j][0], 3) - 960 * pow(pTab[i][j][0], 2) + 320 * pTab[i][j][0];
				y_v		= 0;
				z_u		= (-450 * pow(pTab[i][j][0], 4) + 900 * pow(pTab[i][j][0], 3) - 810 * pow(pTab[i][j][0], 2) + 360 * pTab[i][j][0] - 45) * sin(M_PI * pTab[i][j][1]);
				z_v		= - M_PI * (90 * pow(pTab[i][j][0], 5) - 225 * pow(pTab[i][j][0], 4) + 270 * pow(pTab[i][j][0], 3) - 180 * pow(pTab[i][j][0], 2) + 45 * pTab[i][j][0]) * cos(M_PI * pTab[i][j][1]);

				normal[0] 	= y_u * z_v - z_u * y_v;
				normal[1]	= z_u * x_v - x_u * z_v;
				normal[2]	= x_u * y_v - y_u * x_v;
				length		= sqrt(pow(normal[0], 2) + pow(normal[1], 2) + pow(normal[2], 2));

				if (length == 0) {
					if (i == 0) normal[1] 	= -1;
					// zabezpieczenie przed dzieleniem przez zero
					length = 1;
				}

				if (i >= (r / 2)) {
					normal[0] *= -1;
					normal[1] *= -1;
					normal[2] *= -1;
				}

				normal[0] = normal[0] / length;
				normal[1] = normal[1] / length;
				normal[2] = normal[2] / length;

				if ((j + 1) != r) {

					glBegin(GL_TRIANGLES);
                                                // ustawienie koloru rysowania na bialy
						glColor3f(1.0f, 1.0f, 1.0f);
						glNormal3fv(normal);

						glTexCoord2f((float)i / r, (float)j / r);
						glVertex3fv(tab[i][j]);

						glTexCoord2f((float)(i + 1) / r, (float)j / r);
						glVertex3fv(tab[(i + 1) % r][j]);

						glTexCoord2f((float)i / r, (float)(j + 1) / r);
						glVertex3fv(tab[i][j + 1]);
					glEnd();

					x_u		= (-450 * pow(pTab[(i + 1) % r][j][0], 4) + 900 * pow(pTab[(i + 1) % r][j][0], 3) - 810 * pow(pTab[(i + 1) % r][j][0], 2) + 360 * pTab[(i + 1) % r][j][0] - 45) * cos(M_PI * pTab[(i + 1) % r][j][1]);
					x_v 	= M_PI * (90 * pow(pTab[(i + 1) % r][j][0], 5) - 225 * pow(pTab[(i + 1) % r][j][0], 4) + 270 * pow(pTab[(i + 1) % r][j][0], 3) - 180 * pow(pTab[(i + 1) % r][j][0], 2) + 45 * pTab[(i + 1) % r][j][0]) * sin(M_PI * pTab[(i + 1) % r][j][1]);
					y_u		= 640 * pow(pTab[(i + 1) % r][j][0], 3) - 960 * pow(pTab[(i + 1) % r][j][0], 2) + 320 * pTab[(i + 1) % r][j][0];
					y_v		= 0;
					z_u		= (-450 * pow(pTab[(i + 1) % r][j][0], 4) + 900 * pow(pTab[(i + 1) % r][j][0], 3) - 810 * pow(pTab[(i + 1) % r][j][0], 2) + 360 * pTab[(i + 1) % r][j][0] - 45) * sin(M_PI * pTab[(i + 1) % r][j][1]);
					z_v		= - M_PI * (90 * pow(pTab[(i + 1) % r][j][0], 5) - 225 * pow(pTab[(i + 1) % r][j][0], 4) + 270 * pow(pTab[(i + 1) % r][j][0], 3) - 180 * pow(pTab[(i + 1) % r][j][0], 2) + 45 * pTab[(i + 1) % r][j][0]) * cos(M_PI * pTab[(i + 1) % r][j][1]);

					normal[0] 	= y_u * z_v - z_u * y_v;
					normal[1]	= z_u * x_v - x_u * z_v;
					normal[2]	= x_u * y_v - y_u * x_v;
					length		= sqrt(pow(normal[0], 2) + pow(normal[1], 2) + pow(normal[2], 2));

					if (length == 0) {
						if (i == 0) normal[1] 	= -1;
                                                // zabezpieczenie przed dzieleniem przez zero
						length = 1;
					}

					if (i >= (r / 2)) {
						normal[0] *= -1;
						normal[1] *= -1;
						normal[2] *= -1;
					}

					normal[0] = normal[0] / length;
					normal[1] = normal[1] / length;
					normal[2] = normal[2] / length;

					glBegin(GL_TRIANGLES);
						glNormal3fv(normal);

						glTexCoord2f((float)(i + 1)/ r, (float)j / r);
						glVertex3fv(tab[(i + 1) % r][j]);

						glTexCoord2f((float)(i + 1) / r, (float)(j + 1) / r);
						glVertex3fv(tab[(i + 1) % r][j + 1]);

						glTexCoord2f((float)i / r, (float)(j + 1) / r);
						glVertex3fv(tab[i][j + 1]);
					glEnd();
				}
				else {
					if (i > 0) {
						glBegin(GL_TRIANGLES);
							glNormal3fv(normal);

							glTexCoord2f((float)i / r, (float)j / r);
							glVertex3fv(tab[i][j]);

							glTexCoord2f((float)(i + 1)/ r, (float)j / r);
							glVertex3fv(tab[(i + 1) % r][j]);

							glTexCoord2f((float)(i)/ r, (float)r / r);
							glVertex3fv(tab[r - i][0]);
						glEnd();
					}

					x_u		= (-450 * pow(pTab[(i + 1) % r][j][0], 4) + 900 * pow(pTab[(i + 1) % r][j][0], 3) - 810 * pow(pTab[(i + 1) % r][j][0], 2) + 360 * pTab[(i + 1) % r][j][0] - 45) * cos(M_PI * pTab[(i + 1) % r][j][1]);
					x_v 	= M_PI * (90 * pow(pTab[(i + 1) % r][j][0], 5) - 225 * pow(pTab[(i + 1) % r][j][0], 4) + 270 * pow(pTab[(i + 1) % r][j][0], 3) - 180 * pow(pTab[(i + 1) % r][j][0], 2) + 45 * pTab[(i + 1) % r][j][0]) * sin(M_PI * pTab[(i + 1) % r][j][1]);
					y_u		= 640 * pow(pTab[(i + 1) % r][j][0], 3) - 960 * pow(pTab[(i + 1) % r][j][0], 2) + 320 * pTab[(i + 1) % r][j][0];
					y_v		= 0;
					z_u		= (-450 * pow(pTab[(i + 1) % r][j][0], 4) + 900 * pow(pTab[(i + 1) % r][j][0], 3) - 810 * pow(pTab[(i + 1) % r][j][0], 2) + 360 * pTab[(i + 1) % r][j][0] - 45) * sin(M_PI * pTab[(i + 1) % r][j][1]);
					z_v		= - M_PI * (90 * pow(pTab[(i + 1) % r][j][0], 5) - 225 * pow(pTab[(i + 1) % r][j][0], 4) + 270 * pow(pTab[(i + 1) % r][j][0], 3) - 180 * pow(pTab[(i + 1) % r][j][0], 2) + 45 * pTab[(i + 1) % r][j][0]) * cos(M_PI * pTab[(i + 1) % r][j][1]);

					normal[0] 	= y_u * z_v - z_u * y_v;
					normal[1]	= z_u * x_v - x_u * z_v;
					normal[2]	= x_u * y_v - y_u * x_v;
					length		= sqrt(pow(normal[0], 2) + pow(normal[1], 2) + pow(normal[2], 2));

					if (length == 0) {
						if (i == 0) normal[1] 	= -1;
                                                // zabezpieczenie przed dzieleniem przez zero
						length = 1;
					}

					if (i >= (r / 2)) {
						normal[0] *= -1;
						normal[1] *= -1;
						normal[2] *= -1;
					}

					normal[0] = normal[0] / length;
					normal[1] = normal[1] / length;
					normal[2] = normal[2] / length;

					glBegin(GL_TRIANGLES);
						glNormal3fv(normal);

						glTexCoord2f((float)(i + 1) / r, (float)j / r);
						glVertex3fv(tab[(i + 1) % r][j]);

						glTexCoord2f((float)i / r, (float)r / r);
						glVertex3fv(tab[(r - i) % r][0]);

						glTexCoord2f((float)(i + 1) / r, (float)r / r);
						glVertex3fv(tab[r - i - 1][0]);
					glEnd();

				}
			}
		}
		break;
	}
}

Egg jajko;

/*************************************************************************************/
 // Funkcja wczytuje dane obrazu zapisanego w formacie TGA w pliku o nazwie
 // FileName, alokuje pamięć i zwraca wskaźnik (pBits) do bufora w którym
 // umieszczone są dane.
 // Ponadto udostępnia szerokość (ImWidth), wysokość (ImHeight) obrazu
 // tekstury oraz dane opisujące format obrazu według specyfikacji OpenGL
 // (ImComponents) i (ImFormat).
 // Jest to bardzo uproszczona wersja funkcji wczytującej dane z pliku TGA.
 // Działa tylko dla obrazów wykorzystujących 8, 24, or 32 bitowy kolor.
 // Nie obsługuje plików w formacie TGA kodowanych z kompresją RLE.
/*************************************************************************************/

GLbyte *LoadTGAImage(const char *FileName, GLint *ImWidth, GLint *ImHeight, GLint *ImComponents, GLenum *ImFormat) {
/*************************************************************************************/
// Struktura dla nagłówka pliku  TGA

    #pragma pack(1)
    typedef struct
    {
        GLbyte    idlength;
        GLbyte    colormaptype;
        GLbyte    datatypecode;
        unsigned short    colormapstart;
        unsigned short    colormaplength;
        unsigned char     colormapdepth;
        unsigned short    x_orgin;
        unsigned short    y_orgin;
        unsigned short    width;
        unsigned short    height;
        GLbyte    bitsperpixel;
        GLbyte    descriptor;
    }TGAHEADER;
    #pragma pack(8)

    FILE *pFile;
    TGAHEADER tgaHeader;
    unsigned long lImageSize;
    short sDepth;
    GLbyte    *pbitsperpixel = NULL;

/*************************************************************************************/
// Wartości domyślne zwracane w przypadku błędu

    *ImWidth = 0;
    *ImHeight = 0;
    *ImFormat = GL_BGR_EXT;
    *ImComponents = GL_RGB8;

    pFile = fopen(FileName, "rb");
    if(pFile == NULL)
      return NULL;
/*************************************************************************************/
// Przeczytanie nagłówka pliku

    fread(&tgaHeader, sizeof(TGAHEADER), 1, pFile);

/*************************************************************************************/
// Odczytanie szerokości, wysokości i głębi obrazu

    *ImWidth = tgaHeader.width;
    *ImHeight = tgaHeader.height;
    sDepth = tgaHeader.bitsperpixel / 8;

/*************************************************************************************/
// Sprawdzenie, czy głębia spełnia założone warunki (8, 24, lub 32 bity)

    if(tgaHeader.bitsperpixel != 8 && tgaHeader.bitsperpixel != 24 && tgaHeader.bitsperpixel != 32)
        return NULL;

/*************************************************************************************/
// Obliczenie rozmiaru bufora w pamięci

    lImageSize = tgaHeader.width * tgaHeader.height * sDepth;

/*************************************************************************************/
// Alokacja pamięci dla danych obrazu

     pbitsperpixel = (GLbyte*)malloc(lImageSize * sizeof(GLbyte));

      if(pbitsperpixel == NULL)
        return NULL;

    if(fread(pbitsperpixel, lImageSize, 1, pFile) != 1)
        {
        free(pbitsperpixel);
        return NULL;
        }

/*************************************************************************************/
// Ustawienie formatu OpenGL

    switch(sDepth)
        {
        case 3:
            *ImFormat = GL_BGR_EXT;
            *ImComponents = GL_RGB8;
            break;
        case 4:
            *ImFormat = GL_BGRA_EXT;
            *ImComponents = GL_RGBA8;
            break;
        case 1:
            *ImFormat = GL_LUMINANCE;
            *ImComponents = GL_LUMINANCE8;
            break;
        };

    fclose(pFile);

    return pbitsperpixel;
}
/*************************************************************************************/

void spin() {

	spin_theta += 0.5;
	if( spin_theta > 360.0 ) spin_theta -= 360.0;
	// odświeżenie zawartości aktualnego okna
        glutPostRedisplay();
}

/*************************************************************************************/
// Funkcja rysująca osie układu współrzędnych
void Axes(void) {

	point3  x_min = {-1.0, 0.0, 0.0};
	point3  x_max = { 5.0, 0.0, 0.0};
	// początek i koniec obrazu osi x

	point3  y_min = {0.0, -1.0, 0.0};
	point3  y_max = {0.0,  5.0, 0.0};
	// początek i koniec obrazu osi y

	point3  z_min = {0.0, 0.0, -1.0};
	point3  z_max = {0.0, 0.0,  5.0};
	//  początek i koniec obrazu osi y

	glColor3f(1.0f, 0.0f, 0.0f);  // kolor rysowania osi - czerwony
	glBegin(GL_LINES); // rysowanie osi x
		glVertex3fv(x_min);
		glVertex3fv(x_max);
	glEnd();

	glColor3f(0.0f, 1.0f, 0.0f);  // kolor rysowania - zielony
	glBegin(GL_LINES);  // rysowanie osi y
		glVertex3fv(y_min);
		glVertex3fv(y_max);
	glEnd();

	glColor3f(0.0f, 0.0f, 1.0f);  // kolor rysowania - niebieski
	glBegin(GL_LINES); // rysowanie osi z
		glVertex3fv(z_min);
		glVertex3fv(z_max);
	glEnd();

//	glRotated(60.0, 1.0, 1.0, 1.0 );  // Obrót o 60 stopni
//	glColor3f(1.0f, 1.0f, 1.0f); // Ustawienie koloru rysowania na biały
//	glutWireTeapot(3.0); // Narysowanie obrazu czajnika do herbaty
}
/*************************************************************************************/
// Funkcja określająca co ma być rysowane (zawsze wywoływana gdy trzeba
// przerysować scenę)

void RenderScene(void) {
    
	if(status == 1) {
                                                // jeśli lewy klawisz myszy wcięnięty
	   theta 	+= delta_theta;    	// modyfikacja kąta obrotu o kat proporcjonalny
	   fi 		+= delta_fi;
	}

	if (status == 2) {

		switch (active) {

		case 0:

			l0_theta	+= l0_delta_theta;
			l0_fi		+= l0_delta_fi;
			break;

		case 1:

			l1_theta	+= l1_delta_theta;
			l1_fi		+= l1_delta_fi;
			break;

		case 2:

			l2_theta	+= l2_delta_theta;
			l2_fi		+= l2_delta_fi;
			break;
		}
	}

        // Czyszczenie okna aktualnym kolorem czyszczącym
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Czyszczenie macierzy bieżącej
	glLoadIdentity();

	viewer[0] = radius * cos(theta) * cos(fi);
	viewer[1] = radius * sin(fi);
	viewer[2] = radius * sin(theta) * cos(fi);

	GLfloat	l0_position[4];
	l0_position[0]	= l0_radius * cos(l0_theta) * cos(l0_fi);
	l0_position[1]	= l0_radius * sin(l0_fi);
	l0_position[2]	= l0_radius * sin(l0_theta) * cos(l0_fi);
	l0_position[3]	= 1;

	GLfloat	l1_position[4];
	l1_position[0]	= l1_radius * cos(l1_theta) * cos(l1_fi);
	l1_position[1]	= l1_radius * sin(l1_fi);
	l1_position[2]	= l1_radius * sin(l1_theta) * cos(l1_fi);
	l1_position[3]	= 1;

	GLfloat	l2_position[4];
	l2_position[0]	= l2_radius * cos(l2_theta) * cos(l2_fi);
	l2_position[1]	= l2_radius * sin(l2_fi);
	l2_position[2]	= l2_radius * sin(l2_theta) * cos(l2_fi);
	l2_position[3]	= 1;

	glLightfv(GL_LIGHT0, GL_POSITION, l0_position);
	glLightfv(GL_LIGHT1, GL_POSITION, l1_position);
	glLightfv(GL_LIGHT2, GL_POSITION, l2_position);

	gluLookAt(viewer[0],viewer[1],viewer[2], 0.0, 1.0, 0.0, 0.0, 1.0, 0.0);
	// Zdefiniowanie położenia obserwatora
	//    Axes();
	// Narysowanie osi przy pomocy funkcji zdefiniowanej wyżej

	// obracanie wokół osi y
        glRotatef(spin_theta, 0.0, 1.0, 0.0);

	jajko.rysuj(); // Narysowanie jajka

	glFlush();
        // Przekazanie poleceń rysujących do wykonania

	glutSwapBuffers();
 }

/*************************************************************************************/
// Funkcja ustalająca stan renderowania

void MyInit(void) {
	/*************************************************************************************/
	// Zmienne dla obrazu tekstury

	 GLbyte *pBytes;
	 GLint ImWidth, ImHeight, ImComponents;
	 GLenum ImFormat;

	           // ..................................
	           //       Pozostała część funkcji MyInit()
	           // ..................................

	// Kolor czyszcący (wypełnienia okna) ustawiono na czarny
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	/*************************************************************************************/
	//  Definicja materiału z jakiego zrobiony jest czajnik
	//  i definicja źródła światła
	/*************************************************************************************/

	/*************************************************************************************/
	// Definicja materiału z jakiego zrobiony jest czajnik

	    GLfloat mat_ambient[]  = {1.0, 1.0, 1.0, 1.0};
	    // współczynniki ka =[kar,kag,kab] dla światła otoczenia

	    GLfloat mat_diffuse[]  = {1.0, 1.0, 1.0, 1.0};
	    // współczynniki kd =[kdr,kdg,kdb] światła rozproszonego

	    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
	    // współczynniki ks =[ksr,ksg,ksb] dla światła odbitego

	    GLfloat mat_shininess  = {20.0};
	    // współczynnik n opisujący połysk powierzchni

	/*************************************************************************************/
	// Definicja źródła światła

	    GLfloat light0_position[] = {0.0, 0.0, 10.0, 1.0};
	    // położenie źródła

	    GLfloat light0_ambient[] = {0.1, 0.1, 0.1, 1.0};
	    // składowe intensywności świecenia źródła światła otoczenia
	    // Ia = [Iar,Iag,Iab]

	    GLfloat light0_diffuse[] = {1.0, 1.0, 1.0, 1.0};
	    // składowe intensywności świecenia źródła światła powodującego
	    // odbicie dyfuzyjne Id = [Idr,Idg,Idb]

	    GLfloat light0_specular[]= {1.0, 1.0, 1.0, 1.0};
	    // składowe intensywności świecenia źródła światła powodującego
	    // odbicie kierunkowe Is = [Isr,Isg,Isb]

	    GLfloat light1_position[] = {0.0, 0.0, 10.0, 1.0};
	    // położenie źródła

	    GLfloat light1_ambient[] = {0.1, 0, 0, 1.0};
	    // składowe intensywności świecenia źródła światła otoczenia
	    // Ia = [Iar,Iag,Iab]

	    GLfloat light1_diffuse[] = {1.0, 0, 0, 1.0};
	    // składowe intensywności świecenia źródła światła powodującego
	    // odbicie dyfuzyjne Id = [Idr,Idg,Idb]

	    GLfloat light1_specular[]= {0.8, 0.8, 0.8, 1.0};
	    // składowe intensywności świecenia źródła światła powodującego
	    // odbicie kierunkowe Is = [Isr,Isg,Isb]

	    GLfloat light2_position[] = {0.0, 0.0, 10.0, 1.0};
	    // położenie źródła

	    GLfloat light2_ambient[] = {0, 0, 0.1, 1.0};
	    // składowe intensywności świecenia źródła światła otoczenia
	    // Ia = [Iar,Iag,Iab]

	    GLfloat light2_diffuse[] = {0, 0, 1.0, 1.0};
	    // składowe intensywności świecenia źródła światła powodującego
	    // odbicie dyfuzyjne Id = [Idr,Idg,Idb]

	    GLfloat light2_specular[]= {0.8, 0.8, 0.8, 1.0};
	    // składowe intensywności świecenia źródła światła powodującego
	    // odbicie kierunkowe Is = [Isr,Isg,Isb]

	    GLfloat att_constant  = {1.0};
	    // składowa stała ds dla modelu zmian oświetlenia w funkcji
	    // odległości od źródła

	    GLfloat att_linear    = {0.05};
	    // składowa liniowa dl dla modelu zmian oświetlenia w funkcji
	    // odległości od źródła

	    GLfloat att_quadratic  = {0.001};
	    // składowa kwadratowa dq dla modelu zmian oświetlenia w funkcji
	    // odległości od źródła

	/*************************************************************************************/

	// Ustawienie parametrów materiału i źródła światła

	/*************************************************************************************/
	// Ustawienie patrametrów materiału

	    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	    glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

	/*************************************************************************************/
	// Ustawienie parametrów źródeł

	    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	    glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
	    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

	    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, att_constant);
	    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, att_linear);
	    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, att_quadratic);

	    glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	    glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
	    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);

	    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, att_constant);
	    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, att_linear);
	    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, att_quadratic);

	    glLightfv(GL_LIGHT2, GL_AMBIENT, light2_ambient);
	    glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
	    glLightfv(GL_LIGHT2, GL_SPECULAR, light2_specular);
	    glLightfv(GL_LIGHT2, GL_POSITION, light2_position);

	    glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, att_constant);
	    glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, att_linear);
	    glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, att_quadratic);
	/*************************************************************************************/
	// Ustawienie opcji systemu oświetlania sceny

	    glShadeModel(GL_SMOOTH); // właczenie łagodnego cieniowania
	    glEnable(GL_DEPTH_TEST); // włączenie mechanizmu z-bufora

	/*************************************************************************************/
	/*************************************************************************************/
	// Teksturowanie będzie prowadzone tyko po jednej stronie ściany



	/*************************************************************************************/
   	//  Przeczytanie obrazu tekstury z pliku o nazwie tekstura.tga
	    pBytes = LoadTGAImage("P3_t.tga", &ImWidth, &ImHeight, &ImComponents, &ImFormat);

	/*************************************************************************************/
	// Zdefiniowanie tekstury 2-D

	    glTexImage2D(GL_TEXTURE_2D, 0, ImComponents, ImWidth, ImHeight, 0, ImFormat, GL_UNSIGNED_BYTE, pBytes);

	/*************************************************************************************/
	// Zwolnienie pamięci

	    free(pBytes);

	/*************************************************************************************/
	// Ustalenie trybu teksturowania

	    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	/*************************************************************************************/
	// Określenie sposobu nakładania tekstur

	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	    	           // ..................................
	    	           //       Pozostała część funkcji MyInit()
	    	           // ..................................
}
/*************************************************************************************/
// Funkcja ma za zadanie utrzymanie stałych proporcji rysowanych
// w przypadku zmiany rozmiarów okna.
// Parametry vertical i horizontal (wysokość i szerokość okna) są
// przekazywane do funkcji za każdym razem gdy zmieni się rozmiar okna.

void ChangeSize(GLsizei horizontal, GLsizei vertical ) {
    
    glMatrixMode(GL_PROJECTION);
    // Przełączenie macierzy bieżącej na macierz projekcji

    glLoadIdentity();
    // Czyszcznie macierzy bieżącej

    gluPerspective(70, 1.0, 1.0, 30.0);
    // Ustawienie parametrów dla rzutu perspektywicznego


    if(horizontal <= vertical)
        glViewport(0, (vertical-horizontal)/2, horizontal, horizontal);

    else
        glViewport((horizontal-vertical)/2, 0, vertical, vertical);
    // Ustawienie wielkości okna okna widoku (viewport) w zależności
    // relacji pomiędzy wysokością i szerokością okna

    glMatrixMode(GL_MODELVIEW);
    // Przełączenie macierzy bieżącej na macierz widoku modelu

    glLoadIdentity();
    // Czyszczenie macierzy bieżącej
}

void keys(unsigned char key, int x, int y) {

    switch (key){
        
    case 'p':
        
        if (model == 5) {
        
            glDisable(GL_LIGHTING);             // wyłaczenie systemu oświetlenia sceny
            glDisable(GL_LIGHT0);		// wyłączenie źródła o numerze 1
            glDisable(GL_TEXTURE_2D);           // wyłączenie teksturowania
            lights	= 0;
        }
        model = 1;
        break;
    
    case 'w':
    
        if (model == 5) {
        
            glDisable(GL_LIGHTING);             // wyłaczenie systemu oświetlenia sceny
            glDisable(GL_LIGHT0);		// wyłączenie źródła o numerze 1
            glDisable(GL_TEXTURE_2D);           // wyłączenie teksturowania
            lights	= 0;
        }
        model = 2;
        break;
    
    case 's':
        
        if (model == 5) {
        
            glDisable(GL_LIGHTING);             // wyłaczenie systemu oświetlenia sceny
            glDisable(GL_LIGHT0);		// wyłączenie źródła o numerze 1
            glDisable(GL_TEXTURE_2D);           // wyłączenie teksturowania
            lights	= 0;
        }
        model = 3;
        break;
    
    case 't':
        
        if (model == 5) {
        
            glDisable(GL_LIGHTING);             // wyłaczenie systemu oświetlenia sceny
            glDisable(GL_LIGHT0);		// wyłączenie źródła o numerze 1
            glDisable(GL_TEXTURE_2D);           // wyłączenie teksturowania
            lights	= 0;
        }
        model = 4;
        break;
    
    case 'i':

        if (model != 5) {

            glEnable(GL_LIGHTING);   	// właczenie systemu oświetlenia sceny
	    glEnable(GL_LIGHT0);     	// włączenie źródła o numerze 0
	    glDisable(GL_LIGHT1);		// wyłączenie źródła o numerze 1
	    glDisable(GL_LIGHT2);		// wyłączenie źródła o numerze 2
	    glEnable(GL_TEXTURE_2D); 	// włączenie teksturowania
	    lights 	= 1;
	    model 	= 5;
	    active  = 0;
	}
	else {

            glDisable(GL_LIGHTING);   	// wyłaczenie systemu oświetlenia sceny
	    glDisable(GL_LIGHT0);		// wyłączenie źródła o numerze 1
	    glDisable(GL_TEXTURE_2D); 	// wyłączenie teksturowania
	    lights	= 0;
	    model	= 3;
	}
        break;
    
    case 'l':

        if (lights == 0) {

            glEnable(GL_LIGHTING);   	// właczenie systemu oświetlenia sceny
            glEnable(GL_LIGHT0);     	// włączenie źródła o numerze 0
            lights 	= 1;
            model 	= 4;
            active      = 0;
        }
        else {

            glDisable(GL_TEXTURE_2D); 	// wyłączenie teksturowania
            glDisable(GL_LIGHTING);   	// wyłaczenie systemu oświetlenia sceny
            glDisable(GL_LIGHT0);     	// wyłączenie źródła o numerze 0
            glDisable(GL_LIGHT1);    	// wyłączenie źródła o numerze 1
            glDisable(GL_LIGHT2);     	// wyłączenie źródła o numerze 2
            lights 	= 0;
        }
        break;
    
    case '1':

    	switch (lights) {

    	case 1:

            glDisable(GL_LIGHT0);     // wyłączenie źródła o numerze 0
            glEnable(GL_LIGHT1);      // włączenie źródła o numerze 1
            lights	= 2;
            active	= 1;
            break;

    	case 2:

            glEnable(GL_LIGHT0);      // włączenie źródła o numerze 0
            glDisable(GL_LIGHT1);     // wyłączenie źródła o numerze 1
            lights	= 1;
            active	= 0;
            break;

    	case 3:

            glEnable(GL_LIGHT1);      // włączenie źródła o numerze 1
            lights	= 4;
            active	= 1;
            break;

    	case 4:

            glDisable(GL_LIGHT1);     // wyłączenie źródła o numerze 1
            lights	= 3;
            active	= 2;
            break;
    	}
    
    case '2':

        switch (lights) {

        case 1:

            glDisable(GL_LIGHT0);     // wyłączenie źródła o numerze 0
            glEnable(GL_LIGHT2);      // włączenie źródła o numerze 2
            lights	= 3;
            active	= 2;
            break;

        case 2:

            glEnable(GL_LIGHT2);      // włączenie źródła o numerze 2
            lights	= 4;
            active	= 2;
            break;

        case 3:

            glDisable(GL_LIGHT2);      // włączenie źródła o numerze 2
            glEnable(GL_LIGHT0);       // włączenie źródła o numerze 0
            lights	= 1;
            active	= 0;
            break;

        case 4:

            glDisable(GL_LIGHT2);     // wyłączenie źródła o numerze 1
            lights	= 2;
            active	= 1;
            break;
        }
    }

    // przerysowanie obrazu sceny
    RenderScene();
}

void Mouse(int btn, int state, int x, int y) {

    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

        theta_pos_old           = x;   	// przypisanie aktualnie odczytanej pozycji kursora
        fi_pos_old 		= y;	// jako pozycji poprzedniej
        status 			= 1;    // wcięnięty został lewy klawisz myszy
    }
    else {

    	if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {

    		l0_theta_pos_old	= x;
    		l0_fi_pos_old		= y;
    		l1_theta_pos_old	= x;
    		l1_fi_pos_old		= y;
    		l2_theta_pos_old	= x;
    		l2_fi_pos_old		= y;
    		status			= 2;
    	}
    	else status 			= 0;	// nie został wcięnięty żaden klawisz
    }
}

/*************************************************************************************/

// Funkcja "monitoruje" położenie kursora myszy i ustawia wartości odpowiednich
// zmiennych globalnych

void Motion( GLsizei x, GLsizei y ) {

    delta_theta 		= (x - theta_pos_old) * 0.05;       // obliczenie różnicy położenia kursora myszy
    delta_fi 			= (y - fi_pos_old) * 0.05;

    theta_pos_old 		= x;                                // podstawienie bieżącego położenia jako poprzednie
    fi_pos_old 			= y;

    l0_delta_theta 		= (x - l0_theta_pos_old) * 0.01;    // obliczenie różnicy położenia kursora myszy
    l0_delta_fi 		= (y - l0_fi_pos_old) * 0.01;

    l0_theta_pos_old            = x;                                // podstawienie bieżącego położenia jako poprzednie
    l0_fi_pos_old 		= y;

    l1_delta_theta 		= (x - l1_theta_pos_old) * 0.01;    // obliczenie różnicy położenia kursora myszy
    l1_delta_fi 		= (y - l1_fi_pos_old) * 0.01;

    l1_theta_pos_old            = x;                                // podstawienie bieżącego położenia jako poprzednie
    l1_fi_pos_old 		= y;

    l2_delta_theta 		= (x - l2_theta_pos_old) * 0.01;    // obliczenie różnicy położenia kursora myszy
    l2_delta_fi 		= (y - l2_fi_pos_old) * 0.01;

    l2_theta_pos_old            = x;                                // podstawienie bieżącego położenia jako poprzednie
    l2_fi_pos_old 		= y;

    glutPostRedisplay();                                            // przerysowanie obrazu sceny
}


/*************************************************************************************/
// Główny punkt wejścia programu. Program działa w trybie konsoli

int main(int argc, char **argv) {

	srand( time( NULL ) );

	cout << "p - punkty" << endl;
	cout << "w - siatka" << endl;
	cout << "t - wypelnione trojkaty" << endl;
	cout << "s - wypelnione, kolorowane trojkaty" << endl;
	cout << "l - wlaczenie/wylaczenie oswietlenia (bialego)" << endl;
	cout << "\t 1 wlaczenie/wylaczenie oswietlenia czerwonego" << endl;
	cout << "\t 2 wlaczenie/wylaczenie oswietlenia niebieskiego" << endl;
	cout << "i - wlaczenie/wylaczenie teksturowania ze swiatlem bialym" << endl;
        
	// This is init function
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(600, 600);

	glutCreateWindow("Jajko");

	glutDisplayFunc(RenderScene);
        // Określenie, że funkcja RenderScene będzie funkcją zwrotną
        // (callback function).  Bedzie ona wywoływana za każdym razem
        // gdy zajdzie potrzba przeryswania okna

	glutReshapeFunc(ChangeSize);
        // Dla aktualnego okna ustala funkcję zwrotną odpowiedzialną
        // zazmiany rozmiaru okna

	MyInit();
	// Funkcja MyInit() (zdefiniowana powyżej) wykonuje wszelkie
	// inicjalizacje konieczne  przed przystąpieniem do renderowania

	glutKeyboardFunc(keys);
        
	glutMouseFunc(Mouse);
	// Ustala funkcję zwrotną odpowiedzialną za badanie stanu myszy

	glutMotionFunc(Motion);
	// Ustala funkcję zwrotną odpowiedzialną za badanie ruchu myszy

	glutIdleFunc(spin);

	glutMainLoop();
        // Funkcja uruchamia szkielet biblioteki GLUT
	
        return 0;
}
