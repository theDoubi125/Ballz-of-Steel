#ifndef CHARGING_BALL_H_INCLUDED
#define CHARGING_BALL_H_INCLUDED

class ChargingBall : public Ball
{
public:
    ChargingBall(Player &Player, Vec pos, double r, double m, Vec speed, int chargingTime, int maxHealth);
    virtual sf::Color getColor() const;
    virtual sf::Color getSelectedColor() const;
    virtual void updateBall();
    virtual void throwBall(Vec pos, Vec dir);

private:
    int m_movingTime, m_chargingTime;
    sf::Color m_chargingCol, m_selectedChargingCol;
};

#endif // CHARGING_BALL_H_INCLUDED
