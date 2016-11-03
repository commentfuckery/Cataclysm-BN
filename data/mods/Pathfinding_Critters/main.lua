monster_types = game.get_monster_types()

for _, monster_type in ipairs(monster_types) do
    local mtype = monster_type:obj()
    mtype.path_settings.max_dist = 60
    mtype.path_settings.max_length = 1000
    mtype.path_settings.path_complexity = 20
    mtype.path_settings.bash_strength = mtype.bash_skill
    mtype.path_settings.avoid_allies = true
end
