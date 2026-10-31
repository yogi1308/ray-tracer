vim.g.c_syntax_for_h = true
local function run_in_bottom_terminal(command)
	local terminal_win
	local terminal_row = -1

	for _, win in ipairs(vim.api.nvim_list_wins()) do
		local config = vim.api.nvim_win_get_config(win)
		local buf = vim.api.nvim_win_get_buf(win)
		local row = vim.api.nvim_win_get_position(win)[1]
		local height = vim.api.nvim_win_get_height(win)

		if config.relative == "" and vim.bo[buf].buftype == "terminal" and row + height >= vim.o.lines - 3 then
			if row > terminal_row then
				terminal_win = win
				terminal_row = row
			end
		end
	end

	if terminal_win then
		vim.api.nvim_set_current_win(terminal_win)
		local buf = vim.api.nvim_win_get_buf(terminal_win)
		local job_id = vim.b[buf].terminal_job_id
		if job_id then
			local sent = pcall(vim.fn.chansend, job_id, command .. "\n")
			if sent then
				return
			end
		end

		local new_job_id = vim.fn.termopen(vim.o.shell)
		vim.fn.chansend(new_job_id, command .. "\n")
		return
	end

	vim.cmd("botright split")
	vim.cmd("resize 25")
	vim.cmd("terminal")
	vim.fn.chansend(vim.b.terminal_job_id, command .. "\n")
end

vim.keymap.set("n", "<leader>cb", function()
	run_in_bottom_terminal("make")
end, { desc = "Build with Makefile" })

vim.keymap.set("n", "<leader>cr", function()
	run_in_bottom_terminal("make run")
end, { desc = "Run with Makefile" })

vim.keymap.set("n", "<leader>cx", function()
	run_in_bottom_terminal("make run")
end, { desc = "Build and run with Makefile" })

vim.keymap.set("n", "<leader>ct", function()
	run_in_bottom_terminal("make run")
end, { desc = "Build and run with Makefile" })

