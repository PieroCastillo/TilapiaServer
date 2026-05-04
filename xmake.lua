set_languages("c++23")

add_rules("mode.debug", "mode.release")
add_rules("plugin.compile_commands.autoupdate", {outputdir = ".vscode"})

local libs = {
    "Tilapia.IRLib",
    "Tilapia.Platform"
}

local apps = {
    { name = "Tilapia.CLI", deps = { "Tilapia.Platform" } },
    { name = "Tilapia.Daemon", deps = { "Tilapia.Platform" } },
    { name = "Tilapia.Runtime", deps = { "Tilapia.IRLib", "Tilapia.Platform" } },
    { name = "Tilapia.IRVis", deps = { "Tilapia.IRLib" } },
}

local tests = {
    { name = "makeBin", deps = { "Tilapia.IRLib" } },
}

for _, libname in ipairs(libs) do
    target(libname)
        set_kind("static")
        add_files("src/" .. libname .. "/**.cppm", {public = true})
        local srcFiles = os.files("src/" .. libname .. "/**.cpp")
        if #srcFiles > 0 then
            add_files(srcFiles)
        end
        set_policy("build.c++.modules", true)
        set_policy("build.optimization.lto", true)

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