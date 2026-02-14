use std::process::{Command, Child};
use std::thread;
use std::env;
use std::path::Path;
use std::time::Duration;

struct Manager {
    processes: Vec<Child>,
}

impl Manager {
    fn new() -> Self {
        Self { processes: Vec::new() }
    }
    fn spawn_process1(&mut self, path: &str) {
        let child = Command::new(path)
            .spawn()
            .expect(&format!("Failed to start {}", path));
        self.processes.push(child);
    }
    fn spawn_process(&mut self, executable_path: &str, working_dir: &str) {
        let child = Command::new(executable_path)
            .current_dir(working_dir) // This "teleports" the process to this folder before starting
            .spawn()
            .expect(&format!("Failed to start {} in {}", executable_path, working_dir));
            
        self.processes.push(child);
    }
}

impl Drop for Manager {
    fn drop(&mut self) {
        for child in &mut self.processes {
            let _ = child.kill(); // Ensure children die when Rust manager exits
        }
    }
}

fn main() {
    let mut manager = Manager::new();

    println!("--- Starting RouDi (Memory Manager) ---");
    // You must have iox-roudi installed in your path
   // manager.spawn_process1("iox-roudi");

    // Give RouDi a second to initialize shared memory segments
    thread::sleep(Duration::from_secs(2));

    println!("--- Starting C++ Processes ---");
    let root = Path::new("/");
assert!(env::set_current_dir(&root).is_ok());
println!("Moved to: {}", env::current_dir().unwrap().display());
    
    manager.spawn_process(
        "ROS2_ONLY_test_exec", 
        "../build/Tidalwave_InterfaceApp"
    );
   // manager.spawn_process("");

    println!("All processes running. Press Ctrl+C to stop.");
    
    // Keep the main thread alive
    loop {
        thread::sleep(Duration::from_secs(1));
    }
}