glPushMatrix();
glPushMatrix();
glTranslatef(0, 24, 0);
 // body
glBegin(GL_POLYGON);
glTexCoord2f(0.3125, 0.3125); glVertex3f(-3.5, 6, -1.5);
glTexCoord2f(0.4375, 0.3125); glVertex3f(4.5, 6, -1.5);
glTexCoord2f(0.4375, 0.5); glVertex3f(4.5, -6, -1.5);
glTexCoord2f(0.3125, 0.5); glVertex3f(-3.5, -6, -1.5);
glEnd();

glBegin(GL_LINE_LOOP);
glVertex3f(-3.5, -6, -1.5);
glVertex3f(4.5, -6, -1.5);
glVertex3f(4.5, 6, -1.5);
glVertex3f(-3.5, 6, -1.5);
glEnd();

glBegin(GL_LINE_LOOP);
glVertex3f(-3.5, -6, 2.5);
glVertex3f(-3.5, 6, 2.5);
glVertex3f(4.5, 6, 2.5);
glVertex3f(4.5, -6, 2.5);
glEnd();

glPopMatrix();

glPushMatrix();
glTranslatef(0, 24, 0);
 // head
glBegin(GL_POLYGON);
glTexCoord2f(0.125, 0.125); glVertex3f(-3.5, 5, -3.5);
glTexCoord2f(0.25, 0.125); glVertex3f(4.5, 5, -3.5);
glTexCoord2f(0.25, 0.25); glVertex3f(4.5, -3, -3.5);
glTexCoord2f(0.125, 0.25); glVertex3f(-3.5, -3, -3.5);
glEnd();

glBegin(GL_LINE_LOOP);
glVertex3f(-3.5, -3, -3.5);
glVertex3f(4.5, -3, -3.5);
glVertex3f(4.5, 5, -3.5);
glVertex3f(-3.5, 5, -3.5);
glEnd();

glBegin(GL_LINE_LOOP);
glVertex3f(-3.5, -3, 4.5);
glVertex3f(-3.5, 5, 4.5);
glVertex3f(4.5, 5, 4.5);
glVertex3f(4.5, -3, 4.5);
glEnd();

glPopMatrix();

glPushMatrix();
glTranslatef(5.5, 22, 0);
 // left_arm
glBegin(GL_POLYGON);
glTexCoord2f(0.5625, 0.8125); glVertex3f(-1, 6.1666, -1.5);
glTexCoord2f(0.609375, 0.8125); glVertex3f(2, 6.1666, -1.5);
glTexCoord2f(0.609375, 1); glVertex3f(2, -5.8334, -1.5);
glTexCoord2f(0.5625, 1); glVertex3f(-1, -5.8334, -1.5);
glEnd();

glBegin(GL_LINE_LOOP);
glVertex3f(-1, -5.8334, -1.5);
glVertex3f(2, -5.8334, -1.5);
glVertex3f(2, 6.1666, -1.5);
glVertex3f(-1, 6.1666, -1.5);
glEnd();

glBegin(GL_LINE_LOOP);
glVertex3f(-1, -5.8334, 2.5);
glVertex3f(-1, 6.1666, 2.5);
glVertex3f(2, 6.1666, 2.5);
glVertex3f(2, -5.8334, 2.5);
glEnd();

glPopMatrix();

glPushMatrix();
glTranslatef(-5.5, 22, 0);
 // right_arm
glBegin(GL_POLYGON);
glTexCoord2f(0.6875, 0.3125); glVertex3f(-1, 6.1666, -1.5);
glTexCoord2f(0.734375, 0.3125); glVertex3f(2, 6.1666, -1.5);
glTexCoord2f(0.734375, 0.5); glVertex3f(2, -5.8334, -1.5);
glTexCoord2f(0.6875, 0.5); glVertex3f(-1, -5.8334, -1.5);
glEnd();

glBegin(GL_LINE_LOOP);
glVertex3f(-1, -5.8334, -1.5);
glVertex3f(2, -5.8334, -1.5);
glVertex3f(2, 6.1666, -1.5);
glVertex3f(-1, 6.1666, -1.5);
glEnd();

glBegin(GL_LINE_LOOP);
glVertex3f(-1, -5.8334, 2.5);
glVertex3f(-1, 6.1666, 2.5);
glVertex3f(2, 6.1666, 2.5);
glVertex3f(2, -5.8334, 2.5);
glEnd();

glPopMatrix();

glPushMatrix();
glTranslatef(2, 12, 0);
 // left_leg
glBegin(GL_POLYGON);
glTexCoord2f(0.3125, 0.8125); glVertex3f(-1.5, 6, -1.5);
glTexCoord2f(0.375, 0.8125); glVertex3f(2.5, 6, -1.5);
glTexCoord2f(0.375, 1); glVertex3f(2.5, -6, -1.5);
glTexCoord2f(0.3125, 1); glVertex3f(-1.5, -6, -1.5);
glEnd();

glBegin(GL_LINE_LOOP);
glVertex3f(-1.5, -6, -1.5);
glVertex3f(2.5, -6, -1.5);
glVertex3f(2.5, 6, -1.5);
glVertex3f(-1.5, 6, -1.5);
glEnd();

glBegin(GL_LINE_LOOP);
glVertex3f(-1.5, -6, 2.5);
glVertex3f(-1.5, 6, 2.5);
glVertex3f(2.5, 6, 2.5);
glVertex3f(2.5, -6, 2.5);
glEnd();

glPopMatrix();

glPushMatrix();
glTranslatef(-2, 12, 0);
 // right_leg
glBegin(GL_POLYGON);
glTexCoord2f(0.0625, 0.3125); glVertex3f(-1.5, 6, -1.5);
glTexCoord2f(0.125, 0.3125); glVertex3f(2.5, 6, -1.5);
glTexCoord2f(0.125, 0.5); glVertex3f(2.5, -6, -1.5);
glTexCoord2f(0.0625, 0.5); glVertex3f(-1.5, -6, -1.5);
glEnd();

glBegin(GL_LINE_LOOP);
glVertex3f(-1.5, -6, -1.5);
glVertex3f(2.5, -6, -1.5);
glVertex3f(2.5, 6, -1.5);
glVertex3f(-1.5, 6, -1.5);
glEnd();

glBegin(GL_LINE_LOOP);
glVertex3f(-1.5, -6, 2.5);
glVertex3f(-1.5, 6, 2.5);
glVertex3f(2.5, 6, 2.5);
glVertex3f(2.5, -6, 2.5);
glEnd();

glPopMatrix();

glPopMatrix();

