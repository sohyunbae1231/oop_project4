#ifndef OBJECT_H
#define OBJECT_H

class Object
{
private:
    int x; //x좌표
    int y; //y좌표
    char shape; //모양

public:
    Object(int x, int y, char shape); //생성자; x좌표, y좌표, 모양이 파라미터

    //properties
    int GetX() const;
    void SetX(int x);

    int GetY() const;
    void SetY(int y);

    char GetShape() const;
    void SetShape(char shape);
};

#endif
