#include <cmath>
#include <raylib.h>

// void getIntersection(A, B, C, D) {
//     const tTop = (D.x-C.x) * (A.y-C.y) - (D.y-C.y) * (A.x-C.x);
//     const uTop = (C.y-A.y) * (A.x-B.x) - (C.x-A.x) * (A.y-B.y);
//     const bottom = (D.y-C.y) * (B.x-A.x) - (D.x-C.x) * (B.y-A.y);

//     if (bottom != 0) {
//         const t = tTop/bottom;
//         const u = uTop/bottom;
//         if (t >= 0 && t <= 1 && u >= 0 && u <= 1) {
//             return {
//                 x:lerp(A.x, B.x, t),
//                 y:lerp(A.y, B.y, t),
//                 offset:t
//             }
//         }
//     }

//     return null;
// }

void getIntersection(Vector2 A, Vector2 B, Vector2 C, Vector2 D) {
    double tTop = (D.x-C.x) * (A.y-C.y) - (D.y-C.y) * (A.x-C.x);
    double uTop = (C.y-A.y) * (A.x-B.x) - (C.x-A.x) * (A.y-B.y);
    double bottom = (D.y-C.y) * (B.x-A.x) - (D.x-C.x) * (B.y-A.y);

    if (bottom != 0) {
        double t = tTop/bottom;
        double u = uTop/bottom;
        if (t >= 0 && t <= 1 && u >= 0 && u <= 1) {
            double value[3];
            value[0] = lerp(A.x, B.x, t);
            value[1] = lerp(A.y, B.y, t);
            value[2] = t;
            return ;
        }
    }
}