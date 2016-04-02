local game = {}

function game.init()
    local vertices = {
        0.0, 0.0,
        0.0, 0.5,
        0.5, 0.5,

        0.0, 0.0,
        0.5, 0.0,
        0.5, 0.5,
    }
    game.sq1 = shape(vertices)

    local vertices2 = {
        0.0, 0.0,
        0.0, -0.5,
        -0.5, -0.5,

        0.0, 0.0,
        -0.5, 0.0,
        -0.5, -0.5,
    }
    game.sq2 = shape(vertices2)
end

function game.draw()
    drawShape(game.sq1)
    drawShape(game.sq2)
end

return game
