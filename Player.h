#ifndef PLAYER_H
#define PLAYER_H

class Board;

class Player
{
public:
    Player();
    Player(const int& numero, const bool &ia = false);

    void move(Board& board, const int &di, const int &dj);
    bool canMove(const Board& board, const int& di, const int& dj) const;

    const int& getNumero() const {
        return m_numero;
    }

    const int& getIPos() const {
        return m_iPos;
    }
    void setIPos(const int& i) {
        m_iPos = i;
    }

    const int& getJPos() const {
        return m_jPos;
    }
    void setJPos(const int& j) {
        m_jPos = j;
    }

    const bool& isIA() const {
        return m_IA;
    }

    bool hasWalls() const {
        return m_nbWalls > 0;
    }
    void setWalls(const int& walls) {
        m_nbWalls = walls;
    }
    void decrementWalls() {
        m_nbWalls--;
    }

private:
    int m_iPos;
    int m_jPos;

    int m_numero;
    int m_nbWalls;

    bool m_IA;
};

#endif // PLAYER_H
