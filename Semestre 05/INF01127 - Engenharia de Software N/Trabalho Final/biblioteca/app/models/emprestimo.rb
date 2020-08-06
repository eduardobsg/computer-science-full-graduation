class Emprestimo < ActiveRecord::Base
  belongs_to :pessoa
  belongs_to :item
  has_many :multa
end
