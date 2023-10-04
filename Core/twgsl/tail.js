return Module;
};
(function tryToExport(root, factory) {
    if (typeof exports === 'object' && typeof module === 'object')
      module.exports = factory();
    else if (typeof define === 'function' && define.amd)
      define("twgsl", [], factory);
    else if (typeof exports === 'object')
      exports["twgsl"] = factory();
    else      root["twgsl"] = factory();
  })(typeof self !== "undefined" ? self : typeof global !== "undefined" ? global : this, () => {
    const initialize = (wasmPath) => {
      wasmPath = wasmPath || 'twgsl.wasm'
      return new Promise(resolve => {
          Module({
              locateFile() {
                  return wasmPath;
              },
              onRuntimeInitialized() {
                  var twgsl = this;
                  var wgsl = "";
                  var textDecoder = new TextDecoder();
                  var convertSpirV2WGSL = (code, disableUniformityAnalysis) => {
                    if (!twgsl._return_string_callback) {
                        twgsl._return_string_callback = (data, length) => {
                            const bytes = new Uint8ClampedArray(twgsl.HEAPU8.subarray(data, data + length));
                            wgsl = textDecoder.decode(bytes);
                        };
                    }
                    let addr = twgsl._malloc(code.byteLength);
                    twgsl.HEAPU32.set(code, addr / 4);
                    twgsl._spirv_to_wgsl(addr, code.byteLength, disableUniformityAnalysis);
                    twgsl._free(addr);
                    return wgsl;
                  };
                  resolve({
                    convertSpirV2WGSL: convertSpirV2WGSL,
                  });
              },
          });
      });
    };
    let instance;
    return (wasmPath) => {
        if (!instance) {
            instance = initialize(wasmPath);
        }
        return instance;
    };
});
