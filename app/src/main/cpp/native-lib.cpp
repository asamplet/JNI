#include <jni.h>
#include <string>
#include <GLES2/gl2.h>
#include <GLES/gl.h>

extern "C"
JNIEXPORT void JNICALL
Java_com_example_user_jni_JNIWrapper_onsurfacecreated(JNIEnv *env, jclass cls) {
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glMatrixMode(GL_PROJECTION);
    glOrthof(-8, 8, -8, 8, -8, 8);
    glEnable(GL_DEPTH_TEST); // подключение теста глубины
    glMatrixMode(GL_MODELVIEW);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_user_jni_JNIWrapper_onsurfacechanged(JNIEnv *env, jclass cls, jint width,
                                                      jint height) {
}

GLfloat a[12] = {
        -1, 1, 0,
        -1, -1, 0,
        1, -1, 0,
        1, 1, 0
};

//GLfloat texCoords[8] = { // Texture coords for the above face (NEW)
//        0.0f, 1.0f,  // A. left-bottom (NEW)
//        1.0f, 1.0f,  // B. right-bottom (NEW)
//        0.0f, 0.0f,  // C. left-top (NEW)
//        1.0f, 0.0f   // D. right-top (NEW)
//};

GLfloat texCoords[8] = {
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f
};

int angle = 0;
double angle2 = 0.0F, per = 0.03F, i=1;

extern "C"
JNIEXPORT void JNICALL Java_com_example_user_jni_JNIWrapper_ondrawframe(JNIEnv *env, jclass cls) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glScalef(2, 1.1, 2);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnable(GL_TEXTURE_2D);

    angle = (angle == 360) ? 0 : angle + 1;

    if(angle2 > 1.0F){
        i=-1;
    }
    else if(angle2 < -1.0F) {
        i=1;
    }
    if(angle2*angle2 > 0.81F){
        per=0.013F;
    }
    else if(angle2*angle2 < 0.81F){
        per=0.03F;
    }
    angle2+=per*i;



    glRotatef(angle,0,1,0);
    //glRotatex(angle, 0, 1,0);

    //лицевая грань  ===============================================================
    glPushMatrix();
    glTranslatef(0, angle2/2, 1);

    glVertexPointer(3, GL_FLOAT, 0, a);
    glTexCoordPointer(2, GL_FLOAT, 0, texCoords);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glPopMatrix();

    //задняя грань =================================================================
    glPushMatrix();
    glTranslatef(0, angle2/2, -1);

    glVertexPointer(3, GL_FLOAT, 0, a);
    glTexCoordPointer(2, GL_FLOAT, 0, texCoords);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glPopMatrix();

    //верхняя грань ================================================================
    glPushMatrix();
    glTranslatef(0, 1, 0);

    glRotatef(90, 1, 0, 0);

    glVertexPointer(3, GL_FLOAT, 0, a);
    glTexCoordPointer(2, GL_FLOAT, 0, texCoords);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glPopMatrix();

    //нижняя грань ================================================================
    glPushMatrix();
    glTranslatef(0, -1, 0);

    glRotatef(90, 1, 0, 0);


    glVertexPointer(3, GL_FLOAT, 0, a);
    glTexCoordPointer(2, GL_FLOAT, 0, texCoords);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glPopMatrix();

    //левая грань ================================================================
    glPushMatrix();

    glRotatef(90, 0, 1, 0);

    glTranslatef(0, angle2/2, -1);

    glVertexPointer(3, GL_FLOAT, 0, a);
    glTexCoordPointer(2, GL_FLOAT, 0, texCoords);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glPopMatrix();

    //правая грань ================================================================
    glPushMatrix();

    glRotatef(90, 0, 1, 0);

    glTranslatef(0, angle2/2, 1);

    glVertexPointer(3, GL_FLOAT, 0, a);
    glTexCoordPointer(2, GL_FLOAT, 0, texCoords);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}