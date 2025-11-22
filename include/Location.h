#pragma once

struct Location
{
    int row;
    int col;
    

    Location down() const;
    Location up() const;
    Location right() const;
    Location left() const;
    bool operator==(const Location& other) const = default;
};
