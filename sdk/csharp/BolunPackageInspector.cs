using System;
using System.IO;
using System.IO.Compression;

namespace Bolun.Sdk {
    public static class BolunPackageInspector {
        static bool IsZip(string path) {
            using (var fs = File.OpenRead(path)) {
                return fs.Length >= 2 && fs.ReadByte() == 'P' && fs.ReadByte() == 'K';
            }
        }

        static ushort ReadUInt16LE(byte[] data, int off) {
            return (ushort)(data[off] | (data[off + 1] << 8));
        }

        static uint ReadUInt32LE(byte[] data, int off) {
            return (uint)(data[off] | (data[off + 1] << 8) | (data[off + 2] << 16) | (data[off + 3] << 24));
        }

        static string InspectExe(string path) {
            byte[] h = new byte[512];
            using (var fs = File.OpenRead(path)) {
                int n = fs.Read(h, 0, h.Length);
                if (n < 0x46 || h[0] != 'M' || h[1] != 'Z') return "invalid-exe";
                uint pe = ReadUInt32LE(h, 0x3c);
                if (pe + 6 >= n || h[pe] != 'P' || h[pe + 1] != 'E') return "invalid-pe";
                ushort machine = ReadUInt16LE(h, (int)pe + 4);
                switch (machine) {
                    case 0x01c0:
                    case 0x01c2:
                    case 0x01c4: return "pe/armv7 compatibility-container";
                    case 0xaa64: return "pe/arm64 compatibility-container";
                    case 0x014c: return "pe/x86 unsupported-cpu";
                    case 0x8664: return "pe/x86_64 unsupported-cpu";
                    default: return "pe/unknown-cpu unsupported";
                }
            }
        }

        public static int Main(string[] args) {
            if (args.Length != 1) {
                Console.Error.WriteLine("usage: BolunPackageInspector <xap|appx|apk|exe>");
                return 64;
            }
            string lower = args[0].ToLowerInvariant();
            if (lower.EndsWith(".exe")) {
                Console.WriteLine(InspectExe(args[0]));
                return 0;
            }
            if (!IsZip(args[0])) {
                Console.Error.WriteLine("unsupported package signature");
                return 65;
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
