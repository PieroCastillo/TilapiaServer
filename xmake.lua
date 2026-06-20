set_languages("c++23")

add_rules("mode.debug", "mode.release")
add_rules("plugin.compile_commands.autoupdate", {outputdir = ".vscode"})

local libs = {
    { name = "Tilapia.IRLib", deps = {} },
    { name = "Tilapia.Platform", deps = {} },
    { name = "Tilapia.Protocol", deps = { "Tilapia.Platform" } },
}

local apps = {
    { name = "Tilapia.CLI", deps = { "Tilapia.Platform", "Tilapia.Protocol" } },
    { name = "Tilapia.Daemon", deps = { "Tilapia.Platform", "Tilapia.Protocol" } },
    { name = "Tilapia.Runtime", deps = { "Tilapia.IRLib", "Tilapia.Platform", "Tilapia.Protocol" } },
    { name = "Tilapia.IRVis", deps = { "Tilapia.IRLib" } },
}

local tests = {
    { name = "makeBin", deps = { "Tilapia.IRLib" } },
}

for _, lib in ipairs(libs) do
    target(lib.name)
        set_kind("static")
        add_files("src/" .. lib.name .. "/**.cppm", {public = true})
        local srcFiles = os.files("src/" .. lib.name .. "/**.cpp")
        if #srcFiles > 0 then
            add_files(srcFiles)
        end
        set_policy("build.c++.modules", true)
        set_policy("build.optimization.lto", true)

        if #lib.deps > 0 then
            add_deps(table.unpack(lib.deps))
        end

        if is_plat("windows") then
            add_links("ws2_32")
        end
end

for _, app in ipairs(apps) do
    target(app.name)
        set_kind("binary")
        add_includedirs("include/" .. app.name)
        add_headerfiles("include/" .. app.name .. "/**.hpp")
        add_files("src/" .. app.name .. "/**.cppm")
        add_files("src/" .. app.name .. "/**.cpp")
        set_policy("build.c++.modules", true)
        set_policy("build.optimization.lto", true)

        if #app.deps > 0 then
            add_deps(table.unpack(app.deps))
        end

        if is_plat("windows") then
            add_links("ws2_32")
        end
end

for _, test in ipairs(tests) do
    target(test.name)
        set_kind("binary")
        add_files("tests/" .. test.name .. "/**.cpp")
        set_policy("build.c++.modules", true)

        if #test.deps > 0 then
            add_deps(table.unpack(test.deps))
        end

        if is_plat("windows") then
            add_links("ws2_32")
        end
end