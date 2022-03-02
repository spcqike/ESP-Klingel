Import("env")
import shutil
import time

def after_build(source, target, env): 
    time.sleep(2)
    print("[From Script] Finished building!!")
    shutil.copyfile(".pio/build/d1_mini/firmware.bin", "firmware/firmware.bin")
    print("Firmware moved")

env.AddPostAction("$BUILD_DIR/firmware.bin", after_build)




