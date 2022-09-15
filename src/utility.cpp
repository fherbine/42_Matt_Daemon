#include "../includes/utility.hpp"

pid_t Utility::OS::start_daemon(void) {
    pid_t process_id = 0;
    pid_t sid = 0;

    process_id = fork();
    if (process_id < 0)
        throw OSError();

    // PARENT PROCESS. Need to kill it.
    if (process_id > 0)
        exit(0);

    //unmask the file mode
    umask(0);
    //set new session
    sid = setsid();

    if(sid < 0)
        throw OSError();

    // Change the current working directory to root.
    chdir("/");

    // Close stdin. stdout and stderr
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    return process_id;
}

void Utility::OS::Path::create_folder_tree(std::filesystem::path path) {
    if (std::filesystem::exists(path))
        return ;

    create_folder_tree(path.parent_path());
    std::filesystem::create_directory(path);
}
