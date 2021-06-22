function create_map(w, h, ...)
	local map = {}
	local arg = {...}
	map.w = w
	map.h = h
	for i = 0, w*h-1 do
		map[i] = arg[i+1]
	end
	return map
end

local map = create_map(
	8, 8,
	0,0,0,0,0,1,0,0,
	0,0,1,0,0,1,1,0,
	1,0,0,0,0,0,1,0,
	0,0,1,0,0,0,1,0,
	0,0,1,1,1,0,1,0,
	1,0,1,0,0,0,0,0,
	0,0,0,0,1,1,0,0,
	0,0,0,0,0,1,0,0
)

function slge.init()
	set_window_size(640, 480)
	set_window_title("SLGE Tile Test")
	map.tileset = load_texture("tileset.bmp")
end

map.xo = 0
map.yo = 0
map.xv = 1
map.yv = 1

function slge.draw()
	print("draw")
	for x = 0, map.w-1 do
		for y = 0, map.h-1 do
			local t = map[y*map.w+x]
			draw_texture_region(map.tileset, t*8, 0, 8, 8, map.xo+(x*32), map.yo+(y*32), 32, 32)
		end
	end
end

function slge.update()
	print("update")
	map.xo = map.xo + map.xv
	map.yo = map.yo + map.yv
	if map.xo < 0 or map.xo+map.w*32 >= 640 then
		map.xv *= -1
		map.xo = map.xo + map.xv * 2
	end
	if map.yo < 0 or map.yo+map.h*32 >= 480 then
		map.yv *= -1
		map.yo = map.yo + map.yv * 2
	end
end
