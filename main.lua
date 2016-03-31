local gl = require("libs/luagl/gl") ()
local glfw = require("libs/luajit-glfw/glfw") ()
local GLFW = glfw.const

-- Initialize the library
if glfw.Init() == 0 then
	return
end

local M = nil

local function init(window)
    M = loadfile("game.lua")()
    M:init({
        window = window,
        gl = gl,
        glfw = glfw
    })
end

local function draw()
    M:draw()
end

local function createWindow(opts)
    local primaryMonitor = glfw.GetPrimaryMonitor()
    local vidMode = glfw.GetVideoMode(primaryMonitor)
    local mWidth, mHeight = vidMode.width, vidMode.height

    opts = opts or {}
    opts.title = opts.title or "ShadowGL"
    opts.width = opts.width or mWidth
    opts.height = opts.height or mHeight

    local window = nil

    if opts.fullscreen then
        window = glfw.CreateWindow(opts.width, opts.height, opts.title, primaryMonitor)
    else
        window = glfw.CreateWindow(opts.width, opts.height, opts.title)
    end

    if window == 0 then
        glfw.Terminate()
        return window
    end

    -- Make the window's context current
    window:MakeContextCurrent()
    
    local function toggleFullscreen(window)
        -- Not yet possible! :(
        -- Just waiting on glfwSetWindowMonitor(...) to get released
        -- https://github.com/glfw/glfw/commit/6570d0c4b7a1868ad8af4e61dd5f50bf826d9c76
        --
        -- local windowed = window:GetMonitor() == nil
        -- window:Destroy()
        -- window = createWindow({ fullscreen = windowed })
    end

    local function cb(window, key, scancode, action, mods)
        if key == GLFW.KEY_ESCAPE then
            window:SetShouldClose(true)
        elseif key == GLFW.KEY_F11 then
            toggleFullscreen(window)
        elseif key == GLFW.KEY_R then
            init(window)
        else
            print(key)
        end
    end

    window:SetKeyCallback(cb)

    return window
end

local window = createWindow({ fullscreen = true })

init(window)

-- Loop until the user closes the window
while window:ShouldClose() == 0 do
	-- Render here
	draw()

	-- Swap front and back buffers
	window:SwapBuffers()

	-- Poll for and process events
	glfw.PollEvents()
end

glfw.Terminate()
