set_languages("c++23")

add_rules("mode.debug", "mode.release")
add_rules("plugin.compile_commands.autoupdate", {outputdir = ".vscode"})

local apps = {
    "Tilapia.Daemon",
    "Tilapia.Runtime",
}

for _, appname in ipairs(apps) do
    target(appname)
        set_kind("binary")
        add_includedirs("include/".. appname )
        add_headerfiles("include/" .. appname .. "/**.hpp")
        add_files("src/" .. appname .. "/**.cppm")
        add_files("src/" .. appname .. "/**.cpp")
        set_policy("build.c++.modules", true)
        set_policy("build.optimization.lto", true)
        if is_plat("windows") then
            add_links("ws2_32")
        end
end