assert("sleep works") do
  assert_nothing_raised { sleep(1) }
  assert_nothing_raised { sleep(0) }
end

assert("sleep would accept non-negative float value") do
  skip unless Object.const_defined?(:Float)
  assert_nothing_raised { sleep(0.01) }
  assert_nothing_raised { sleep(0.0) }
  assert_nothing_raised { sleep(-0.0) }
end

assert("sleep would not accept negative integer value") do
  assert_raise(ArgumentError) { sleep(-1) }
end

assert("sleep would not accept negative float value") do
  skip unless Object.const_defined?(:Float)
  assert_raise(ArgumentError) { sleep(-0.1) }
end

assert("usleep works") do
  assert_nothing_raised { usleep(100) }
  assert_nothing_raised { usleep(0) }
end

assert("usleep would not accept negative value") do
  assert_raise(ArgumentError) { usleep(-100) }
end

assert("sleep 0 and usleep 0 return") do
  assert_equal 0, sleep(0)
  assert_equal 0, usleep(0)
end
