using System;
using System.IO;
using System.IO.Compression;

namespace Bolun.Sdk {
    public static class BolunPackageInspector {
        public static int Main(string[] args) {
            if (args.Length != 1) {
                Console.Error.WriteLine("usage: BolunPackageInspector <xap|appx|apk>");
                return 64;
            }
            using (var zip = ZipFile.OpenRead(args[0])) {
                bool manifest = false;
                foreach (var entry in zip.Entries) {
                    string n = entry.FullName.ToLowerInvariant();
                    if (n.EndsWith("wmappmanifest.xml") || n.EndsWith("appxmanifest.xml") || n.EndsWith("androidmanifest.xml")) {
                        manifest = true;
                        Console.WriteLine(entry.FullName + " " + entry.Length + " bytes");
                    }
                }
                return manifest ? 0 : 65;
            }
        }
    }
}
