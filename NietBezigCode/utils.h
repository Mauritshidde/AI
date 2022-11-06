#include <raylib.h>

double lerp(double A, double B, double t) {
    double value = A + (B-A) *t;
    return value;
}

Vector4 getIntersection(Vector2 A, Vector2 B, Vector2 C, Vector2 D) {
    double tTop = (D.x-C.x) * (A.y-C.y) - (D.y-C.y) * (A.x-C.x);
    double uTop = (C.y-A.y) * (A.x-B.x) - (C.x-A.x) * (A.y-B.y);
    double bottom = (D.y-C.y) * (B.x-A.x) - (D.x-C.x) * (B.y-A.y);
    double retVal[3];
    // std::cout << bottom << " " << t;
    Vector4 test;
    if (bottom != 0) {
        double t = tTop/bottom;
        double u = uTop/bottom;
        if (t >= 0 && t <= 1 && u >= 0 && u <= 1) {
            // retVal[0] = lerp(A.x, B.x, t);
            // retVal[1] = lerp(A.y, B.y, t);
            // retVal[2] = t;
            test.x = lerp(A.x, B.x, t);
            test.y = lerp(A.y, B.y, t);
            test.z = t;
            test.w = 5;
            // std::cout << std::endl << "test  " << retVal[2] << std::endl;
            // std::cout << lerp(A.x, B.x, t) << std::endl;
            return test;
        }
    }
    return test;
}