local ffi = require("ffi")

ffi.cdef[[
void createVertexBuffer();
void draw(int, int);
]]

local game = {}

function game:init(ctx)
    self.window, self.gl, self.glfw = ctx.window, ctx.gl, ctx.glfw
    ffi.C.createVertexBuffer()
    --local vertices = {
    --    0.0, 1.0,
    --    -1.0, -1.0,
    --    1.0, -1.0
    --}

    --local buffId = {}
    --self.gl.GenBuffers(1, buffId)
    --self.gl.BindBuffer(self.gl.GL_ARRAY_BUFFER, buffId)
    --self.gl.BufferData(self.gl.GL_ARRAY_BUFFER, 6, vertices, self.gl.GL_STATIC_DRAW)
    --self.gl.EnableVertexAttribArray(0)
    --self.gl.VertexAttribPointer(0, 2, self.gl.GL_FLOAT, self.gl.GL_FALSE, 0, 0)
end

function game:draw()
    local width, height = self.window:GetFramebufferSize() 
    ffi.C.draw(width, height)
end

return game
