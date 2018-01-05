 // 
glPushMatrix();
 // body
glPushMatrix();
glTranslatef(0, 0, 0);
glTranslatef(0, 24, 0);
glBegin(GL_POLYGON);
glTexCoord2f(0.3125, 0.25); glVertex3f(-3.5, 6, 2.5);
glTexCoord2f(0.4375, 0.25); glVertex3f(4.5, 6, 2.5);
glTexCoord2f(0.4375, 0.3125); glVertex3f(4.5, 6, -1.5);
glTexCoord2f(0.3125, 0.3125); glVertex3f(-3.5, 6, -1.5);
glEnd();

glBegin(GL_POLYGON);
glTexCoord2f(0.4375, 0.25); glVertex3f(4.5, -6, 2.5);
glTexCoord2f(0.5625, 0.25); glVertex3f(-3.5, -6, 2.5);
glTexCoord2f(0.5625, 0.3125); glVertex3f(-3.5, -6, -1.5);
glTexCoord2f(0.4375, 0.3125); glVertex3f(4.5, -6, -1.5);
glEnd();

glBegin(GL_POLYGON);
glTexCoord2f(0.25, 0.3125); glVertex3f(-3.5, 6, 2.5);
glTexCoord2f(0.3125, 0.3125); glVertex3f(-3.5, 6, -1.5);
glTexCoord2f(0.3125, 0.5); glVertex3f(-3.5, -6, -1.5);
glTexCoord2f(0.25, 0.5); glVertex3f(-3.5, -6, 2.5);
glEnd();

glBegin(GL_POLYGON);
glTexCoord2f(0.3125, 0.3125); glVertex3f(-3.5, 6, -1.5);
glTexCoord2f(0.4375, 0.3125); glVertex3f(4.5, 6, -1.5);
glTexCoord2f(0.4375, 0.5); glVertex3f(4.5, -6, -1.5);
glTexCoord2f(0.3125, 0.5); glVertex3f(-3.5, -6, -1.5);
glEnd();

glBegin(GL_POLYGON);
glTexCoord2f(0.4375, 0.3125); glVertex3f(4.5, 6, -1.5);
glTexCoord2f(0.5, 0.3125); glVertex3f(4.5, 6, 2.5);
glTexCoord2f(0.5, 0.5); glVertex3f(4.5, -6, 2.5);
glTexCoord2f(0.4375, 0.5); glVertex3f(4.5, -6, -1.5);
glEnd();

glBegin(GL_POLYGON);
glTexCoord2f(0.5, 0.3125); glVertex3f(4.5, 6, 2.5);
glTexCoord2f(0.625, 0.3125); glVertex3f(-3.5, 6, 2.5);
glTexCoord2f(0.625, 0.5); glVertex3f(-3.5, -6, 2.5);
glTexCoord2f(0.5, 0.5); glVertex3f(4.5, -6, 2.5);
glEnd();

glPopMatrix();

 // head
glPushMatrix();
glTranslatef(0, 8, 0);
glTranslatef(0, 24, 0);
glBegin(GL_POLYGON);
glTexCoord2f(0.125, 0); glVertex3f(-3.5, 5, 4.5);
glTexCoord2f(0.25, 0); glVertex3f(4.5, 5, 4.5);
glTexCoord2f(0.25, 0.125); glVertex3f(4.5, 5, -3.5);
glTexCoord2f(0.125, 0.125); glVertex3f(-3.5, 5, -3.5);
glEnd();

glBegin(GL_POLYGON);
glTexCoord2f(0.25, 0); glVertex3f(4.5, -3, 4.5);
glTexCoord2f(0.375, 0); glVertex3f(-3.5, -3, 4.5);
glTexCoord2f(0.375, 0.125); glVertex3f(-3.5, -3, -3.5);
glTexCoord2f(0.25, 0.125); glVertex3f(4.5, -3, -3.5);
glEnd();

glBegin(GL_POLYGON);
glTexCoord2f(0, 0.125); glVertex3f(-3.5, 5, 4.5);
glTexCoord2f(0.125, 0.125); glVertex3f(-3.5, 5, -3.5);
glTexCoord2f(0.125, 0.25); glVertex3f(-3.5, -3, -3.5);
glTexCoord2f(0, 0.25); glVertex3f(-3.5, -3, 4.5);
glEnd();

glBegin(GL_POLYGON);
glTexCoord2f(0.125, 0.125); glVertex3f(-3.5, 5, -3.5);
glTexCoord2f(0.25, 0.125); glVertex3f(4.5, 5, -3.5);
glTexCoord2f(0.25, 0.25); glVertex3f(4.5, -3, -3.5);
glTexCoord2f(0.125, 0.25); glVertex3f(-3.5, -3, -3.5);
glEnd();

glBegin(GL_POLYGON);
glTexCoord2f(0.25, 0.125); glVertex3f(4.5, 5, -3.5);
glTexCoord2f(0.375, 0.125); glVertex3f(4.5, 5, 4.5);
glTexCoord2f(0.375, 0.25); glVertex3f(4.5, -3, 4.5);
glTexCoord2f(0.25, 0.25); glVertex3f(4.5, -3, -3.5);
glEnd();

glBegin(GL_POLYGON);
glTexCoord2f(0.375, 0.125); glVertex3f(4.5, 5, 4.5);
glTexCoord2f(0.5, 0.125); glVertex3f(-3.5, 5, 4.5);
glTexCoord2f(0.5, 0.25); glVertex3f(-3.5, -3, 4.5);
glTexCoord2f(0.375, 0.25); glVertex3f(4.5, -3, 4.5);
glEnd();

glPopMatrix();

 // left_arm
glPushMatrix();
glTranslatef(0, 1.9992, 0);
glTranslatef(5.5, 22, 0);
glBegin(GL_POLYGON);
glTexCoord2f(0.5625, 0.75); glVertex3f(-1, 6.1666, 2.5);
glTexCoord2f(0.609375, 0.75); glVertex3f(2, 6.1666, 2.5);
glTexCoord2f(0.609375, 0.8125); glVertex3f(2, 6.1666, -1.5);
glTexCoord2f(0.5625, 0.8125); glVertex3f(-1, 6.1666, -1.5);
glEnd();

glBegin(GL_POLYGON);
glTexCoord2f(0.609375, 0.75); glVertex3f(2, -5.8334, 2.5);
glTexCoord2f(0.65625, 0.75); glVertex3f(-1, -5.8334, 2.5);
glTexCoord2f(0.65625, 0.8125); glVertex3f(-1, -5.8334, -1.5);
glTexCoord2f(0.609375, 0.8125); glVertex3f(2, -5.8334, -1.5);
glEnd();

glBegin(GL_POLYGON);
glTexCoord2f(0.5, 0.8125); glVertex3f(-1, 6.1666, 2.5);
glTexCoord2f(0.5625, 0.8125); glVertex3f(-1, 6.1666, -1.5);
glTexCoord2f(0.5625, 1); glVertex3f(-1, -5.8334, -1.5);
glTexCoord2f(0.5, 1); glVertex3f(-1, -5.8334, 2.5);
glEnd();

glBegin(GL_POLYGON);
glTexCoord2f(0.5625, 0.8125); glVertex3f(-1, 6.1666, -1.5);
glTexCoord2f(0.609375, 0.8125); glVertex3f(2, 6.1666, -1.5);
glTexCoord2f(0.609375, 1); glVertex3f(2, -5.8334, -1.5);
glTexCoord2f(0.5625, 1); glVertex3f(-1, -5.8334, -1.5);
glEnd();

glBegin(GL_POLYGON);
glTexCoord2f(0.609375, 0.8125); glVertex3f(2, 6.1666, -1.5);
glTexCoord2f(0.671875, 0.8125); glVertex3f(2, 6.1666, 2.5);
glTexCoord2f(0.671875, 1); glVertex3f(2, -5.8334, 2.5);
glTexCoord2f(0.609375, 1); glVertex3f(2, -5.8334, -1.5);
glEnd();

glBegin(GL_POLYGON);
glTexCoord2f(0.671875, 0.8125); glVertex3f(2, 6.1666, 2.5);
glTexCoord2f(0.71875, 0.8125); glVertex3f(-1, 6.1666, 2.5);
glTexCoord2f(0.71875, 1); glVertex3f(-1, -5.8334, 2.5);
glTexCoord2f(0.671875, 1); glVertex3f(2, -5.8334, 2.5);
glEnd();

glPopMatrix();

 // right_arm
glPushMatrix();
glTranslatef(0, 1.9992, 0);
glTranslatef(-5.5, 22, 0);
glBegin(GL_POLYGON);
glTexCoord2f(0.6875, 0.25); glVertex3f(-1, 6.1666, 2.5);
glTexCoord2f(0.734375, 0.25); glVertex3f(2, 6.1666, 2.5);
glTexCoord2f(0.734375, 0.3125); glVertex3f(2, 6.1666, -1.5);
glTexCoord2f(0.6875, 0.3125); glVertex3f(-1, 6.1666, -1.5);
glEnd();

glBegin(GL_POLYGON);
glTexCoord2f(0.734375, 0.25); glVertex3f(2, -5.8334, 2.5);
glTexCoord2f(0.78125, 0.25); glVertex3f(-1, -5.8334, 2.5);
glTexCoord2f(0.78125, 0.3125); glVertex3f(-1, -5.8334, -1.5);
glTexCoord2f(0.734375, 0.3125); glVertex3f(2, -5.8334, -1.5);
glEnd();

glBegin(GL_POLYGON);
glTexCoord2f(0.625, 0.3125); glVertex3f(-1, 6.1666, 2.5);
glTexCoord2f(0.6875, 0.3125); glVertex3f(-1, 6.1666, -1.5);
glTexCoord2f(0.6875, 0.5); glVertex3f(-1, -5.8334, -1.5);
glTexCoord2f(0.625, 0.5); glVertex3f(-1, -5.8334, 2.5);
glEnd();

glBegin(GL_POLYGON);
glTexCoord2f(0.6875, 0.3125); glVertex3f(-1, 6.1666, -1.5);
glTexCoord2f(0.734375, 0.3125); glVertex3f(2, 6.1666, -1.5);
glTexCoord2f(0.734375, 0.5); glVertex3f(2, -5.8334, -1.5);
glTexCoord2f(0.6875, 0.5); glVertex3f(-1, -5.8334, -1.5);
glEnd();

glBegin(GL_POLYGON);
glTexCoord2f(0.734375, 0.3125); glVertex3f(2, 6.1666, -1.5);
glTexCoord2f(0.796875, 0.3125); glVertex3f(2, 6.1666, 2.5);
glTexCoord2f(0.796875, 0.5); glVertex3f(2, -5.8334, 2.5);
glTexCoord2f(0.734375, 0.5); glVertex3f(2, -5.8334, -1.5);
glEnd();

glBegin(GL_POLYGON);
glTexCoord2f(0.796875, 0.3125); glVertex3f(2, 6.1666, 2.5);
glTexCoord2f(0.84375, 0.3125); glVertex3f(-1, 6.1666, 2.5);
glTexCoord2f(0.84375, 0.5); glVertex3f(-1, -5.8334, 2.5);
glTexCoord2f(0.796875, 0.5); glVertex3f(2, -5.8334, 2.5);
glEnd();

glPopMatrix();

 // left_leg
glPushMatrix();
glTranslatef(0, 0, 0);
glTranslatef(2, 12, 0);
glBegin(GL_POLYGON);
glTexCoord2f(0.3125, 0.75); glVertex3f(-1.5, 6, 2.5);
glTexCoord2f(0.375, 0.75); glVertex3f(2.5, 6, 2.5);
glTexCoord2f(0.375, 0.8125); glVertex3f(2.5, 6, -1.5);
glTexCoord2f(0.3125, 0.8125); glVertex3f(-1.5, 6, -1.5);
glEnd();

glBegin(GL_POLYGON);
glTexCoord2f(0.375, 0.75); glVertex3f(2.5, -6, 2.5);
glTexCoord2f(0.4375, 0.75); glVertex3f(-1.5, -6, 2.5);
glTexCoord2f(0.4375, 0.8125); glVertex3f(-1.5, -6, -1.5);
glTexCoord2f(0.375, 0.8125); glVertex3f(2.5, -6, -1.5);
glEnd();

glBegin(GL_POLYGON);
glTexCoord2f(0.25, 0.8125); glVertex3f(-1.5, 6, 2.5);
glTexCoord2f(0.3125, 0.8125); glVertex3f(-1.5, 6, -1.5);
glTexCoord2f(0.3125, 1); glVertex3f(-1.5, -6, -1.5);
glTexCoord2f(0.25, 1); glVertex3f(-1.5, -6, 2.5);
glEnd();

glBegin(GL_POLYGON);
glTexCoord2f(0.3125, 0.8125); glVertex3f(-1.5, 6, -1.5);
glTexCoord2f(0.375, 0.8125); glVertex3f(2.5, 6, -1.5);
glTexCoord2f(0.375, 1); glVertex3f(2.5, -6, -1.5);
glTexCoord2f(0.3125, 1); glVertex3f(-1.5, -6, -1.5);
glEnd();

glBegin(GL_POLYGON);
glTexCoord2f(0.375, 0.8125); glVertex3f(2.5, 6, -1.5);
glTexCoord2f(0.4375, 0.8125); glVertex3f(2.5, 6, 2.5);
glTexCoord2f(0.4375, 1); glVertex3f(2.5, -6, 2.5);
glTexCoord2f(0.375, 1); glVertex3f(2.5, -6, -1.5);
glEnd();

glBegin(GL_POLYGON);
glTexCoord2f(0.4375, 0.8125); glVertex3f(2.5, 6, 2.5);
glTexCoord2f(0.5, 0.8125); glVertex3f(-1.5, 6, 2.5);
glTexCoord2f(0.5, 1); glVertex3f(-1.5, -6, 2.5);
glTexCoord2f(0.4375, 1); glVertex3f(2.5, -6, 2.5);
glEnd();

glPopMatrix();

 // right_leg
glPushMatrix();
glTranslatef(0, 0, 0);
glTranslatef(-2, 12, 0);
glBegin(GL_POLYGON);
glTexCoord2f(0.0625, 0.25); glVertex3f(-1.5, 6, 2.5);
glTexCoord2f(0.125, 0.25); glVertex3f(2.5, 6, 2.5);
glTexCoord2f(0.125, 0.3125); glVertex3f(2.5, 6, -1.5);
glTexCoord2f(0.0625, 0.3125); glVertex3f(-1.5, 6, -1.5);
glEnd();

glBegin(GL_POLYGON);
glTexCoord2f(0.125, 0.25); glVertex3f(2.5, -6, 2.5);
glTexCoord2f(0.1875, 0.25); glVertex3f(-1.5, -6, 2.5);
glTexCoord2f(0.1875, 0.3125); glVertex3f(-1.5, -6, -1.5);
glTexCoord2f(0.125, 0.3125); glVertex3f(2.5, -6, -1.5);
glEnd();

glBegin(GL_POLYGON);
glTexCoord2f(0, 0.3125); glVertex3f(-1.5, 6, 2.5);
glTexCoord2f(0.0625, 0.3125); glVertex3f(-1.5, 6, -1.5);
glTexCoord2f(0.0625, 0.5); glVertex3f(-1.5, -6, -1.5);
glTexCoord2f(0, 0.5); glVertex3f(-1.5, -6, 2.5);
glEnd();

glBegin(GL_POLYGON);
glTexCoord2f(0.0625, 0.3125); glVertex3f(-1.5, 6, -1.5);
glTexCoord2f(0.125, 0.3125); glVertex3f(2.5, 6, -1.5);
glTexCoord2f(0.125, 0.5); glVertex3f(2.5, -6, -1.5);
glTexCoord2f(0.0625, 0.5); glVertex3f(-1.5, -6, -1.5);
glEnd();

glBegin(GL_POLYGON);
glTexCoord2f(0.125, 0.3125); glVertex3f(2.5, 6, -1.5);
glTexCoord2f(0.1875, 0.3125); glVertex3f(2.5, 6, 2.5);
glTexCoord2f(0.1875, 0.5); glVertex3f(2.5, -6, 2.5);
glTexCoord2f(0.125, 0.5); glVertex3f(2.5, -6, -1.5);
glEnd();

glBegin(GL_POLYGON);
glTexCoord2f(0.1875, 0.3125); glVertex3f(2.5, 6, 2.5);
glTexCoord2f(0.25, 0.3125); glVertex3f(-1.5, 6, 2.5);
glTexCoord2f(0.25, 0.5); glVertex3f(-1.5, -6, 2.5);
glTexCoord2f(0.1875, 0.5); glVertex3f(2.5, -6, 2.5);
glEnd();

glPopMatrix();

glPopMatrix();

