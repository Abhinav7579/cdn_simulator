import { exec } from "child_process";
export const runSimulator = () => {
    return new Promise((resolve, reject) => {
        exec("..\\simulator\\main.exe --json", (error, stdout, stderr) => {
            console.log("STDOUT:");
            console.log(stdout);
            console.log("STDERR:");
            console.log(stderr);
            if (error) {
                console.error(error);
                reject(error);
                return;
            }
            try {
                const data = JSON.parse(stdout);
                resolve(data);
            }
            catch (err) {
                console.error(err);
                reject(err);
            }
        });
    });
};
//# sourceMappingURL=simulatorService.js.map