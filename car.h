class Car {
    public:
        Car();
        void Draw();
        double acceleration = 1;
        double speed = 0;
        double maxSpeed = 5;
        Vector2 position;
        const Vector2 size{20, 40};
        double direction = 0;
        double angle;
};

Car::Car() {

}