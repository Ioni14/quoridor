#ifndef PLAYER_H
#define PLAYER_H

class Board;

class Player
{
public:
    Player();
    Player(const int& numero, const int& nbWalls);

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

    bool hasWalls() const {
        return m_nbWalls > 0;
    }

    void decrementWalls() {
        m_nbWalls--;
    }

private:
    int m_iPos;
    int m_jPos;

    int m_numero;
    int m_nbWalls;
};

#endif // PLAYER_H
