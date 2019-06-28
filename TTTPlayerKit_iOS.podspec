Pod::Spec.new do |spec|
  spec.name         = "TTTPlayerKit_iOS"
  spec.version      = "1.0"
  spec.summary      = "TTTPlayerKit_iOS"
  spec.description  = "first install the framework"

  spec.homepage     = "https://github.com/santiyun/TTTPlayerKit_iOS"
  spec.license      = "MIT"

  spec.author             = { "santiyun" => "sdyzsdut@163.com" }

  spec.platform     = :ios, "8.0"
  spec.source       = { :git => "https://github.com/santiyun/TTTPlayerKit_iOS.git", :tag => "1.0" }

  spec.vendored_frameworks = '*.framework'
  #spec.vendored_libraries = '*.a'

  spec.libraries    = "z", "c++"
  #spec.library   = "z"
  #spec.frameworks = 'AVFoundation', 'AudioToolbox'

  spec.pod_target_xcconfig = { 'VALID_ARCHS[sdk=iphonesimulator*]' => '' }

end
