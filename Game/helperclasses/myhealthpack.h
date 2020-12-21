#ifndef MYHEALTHPACK_H
#define MYHEALTHPACK_H

class MyHealthpack
{
public:
    MyHealthpack(int x,int y,float value);

    float getHealth() const;
    void setHealth(float value);

    int getX() const;
    int getY() const;
    bool getUsed() const;
    void setUsed(bool value);

private:
    int x, y;
    bool used = false;
    float health;
};

#endif // MYHEALTHPACK_H
