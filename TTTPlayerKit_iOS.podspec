Pod::Spec.new do |spec|
  spec.name         = "TTTPlayerKit_iOS"
  spec.version      = "1.3"
  spec.summary      = "TTTPlayerKit_iOS"
  spec.description  = "TTTPlayerKit_iOS for open video 1s"

  spec.homepage     = "https://github.com/santiyun/TTTPlayerKit_iOS"
  spec.license      = "MIT"

  spec.author             = { "santiyun" => "sdyzsdut@163.com" }

  spec.platform     = :ios, "8.0"
  spec.source       = { :git => "https://github.com/santiyun/TTTPlayerKit_iOS.git", :tag => "1.3" }

  spec.vendored_frameworks = '*.framework'
  #spec.vendored_libraries = '*.a'

  spec.libraries    = "z", "c++"
  #spec.library   = "z"
  #spec.frameworks = 'AVFoundation', 'AudioToolbox'

  spec.pod_target_xcconfig = { 'VALID_ARCHS[sdk=iphonesimulator*]' => '' }

  spec.user_target_xcconfig =  { 'ENABLE_BITCODE' => 'NO' }

end
