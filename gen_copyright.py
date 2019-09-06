import os
import json

def getAllFiles(root_dir, suffix = []):
	ret = []
	for root, dirs, files in os.walk(root_dir):
		if root.find(".svn") >= 0:
			continue
		for file in files:
			if not suffix:
				ret.append(os.path.join(root,file))
			else:
				base, suf = os.path.splitext(file)
				if suf in suffix:
					ret.append(os.path.join(root,file))
	return ret


copyrightTemplate = '''/* @Copyright (c) 2019 by Yukun Xie
 *
 * {filename}
 *
 * This file is part of the "KASA" project (Copyright (c) 2019 by Yukun Xie)
 * See "LICENSE.txt" for license information.
 */

'''


for file in getAllFiles("./", [".cpp", ".h"]):
    text = ""
    with open(file, "r") as fd:
        text = fd.read()
        fd.close()
    if text.find("/* @Copyright") < 0:
        copyright = copyrightTemplate.format(filename = file)
        text = copyright + text

        newFilename = file + ".new"
        with open(newFilename, "w") as fd:
            fd.write(text)

        os.rename(newFilename, file)

